/* 
*************************************************************************
 break ACD files in c
 assumes valid input through command line: 
	(A source directory and a dest directory)
 to compile> gcc -o break BreakACSFiles.c
 to run> ./break FilesToProcess/ Output/
*************************************************************************
*/

#include<stdio.h>  // reading & printing
#include<dirent.h> // directory reading
#include<string.h> // string manipulations

// function prototypes
int processDirs(char *, char *);
int processFile(char *, char *, char *);

enum { IN_SIZE = 500 }; // string size for input

int main(int argc, char *argv[]) {
    char src[IN_SIZE], dest[IN_SIZE];
    int fp = 0;

    if(argc != 3) {
	printf("Error: Input requires a source and destination path: > ./break FilesToProcess/ Output/ \n");
	return 0;
    }

    strcpy(src,argv[1]);
    strcpy(dest,argv[2]);
    fp = processDirs(src,dest);
    printf("Processed %d files\n", fp);
	
    return 1;
}

int processDirs(char *s, char *d) {
    DIR *dir, *dir2;
    struct dirent *files;
    char src[IN_SIZE], dest[IN_SIZE];
    int fp = 0, rp = 0;

    if(((dir=opendir(s)) != NULL) && ((dir2=opendir(d))!=NULL)) {
	while ((files=readdir(dir)) != NULL) {
	    if(strncmp(files->d_name,".",1) != 0) {
	    	//printf("%s \n", files->d_name);
		rp = processFile(s, files->d_name, d);		
		if(rp > 0) { 
		    printf("Total Records Processed: %d\n", rp);
		    fp += 1; 
		}
	    }
	}
	close(dir);
	close(dir2);
    } else {
	printf("Error: One or more of the paths provided do not exist.");
   	return 0;
    }

    return fp;
}

int processFile(char *srcPath, char *srcFil, char *dstDir) {
    int ap = 0, cp = 0, dp = 0;
    char line[IN_SIZE], sFile[IN_SIZE], dFile[IN_SIZE], 
	 aPath[IN_SIZE], cPath[IN_SIZE], dPath[IN_SIZE];
    FILE *srcFile, *aDstFile, *cDstFile, *dDstFile;

    // make sure file paths is completely empty
    line[0] = '\0'; 
    sFile[0] = '\0'; 
    dFile[0] = '\0';
    aPath[0] = '\0';
    cPath[0] = '\0';
    dPath[0] = '\0';

    // set up file paths
    strcat(sFile, srcPath);
    strcat(sFile, srcFil);
    strcat(aPath, dstDir);
    strcat(aPath,"A_");
    strcat(aPath,srcFil);
    strcat(cPath, dstDir);
    strcat(cPath,"C_");
    strcat(cPath,srcFil);
    strcat(dPath, dstDir);
    strcat(dPath,"D_");
    strcat(dPath,srcFil);

    printf("Opening: %s\n", sFile);
/*
    printf("Opening: %s\n", aPath);
    printf("Opening: %s\n", cPath);
    printf("Opening: %s\n", dPath);
*/
    srcFile = fopen(sFile,"r");
    aDstFile = fopen(aPath,"a");
    cDstFile = fopen(cPath,"a"); 
    dDstFile = fopen(dPath,"a");
    
    if(srcFile && aDstFile && cDstFile && dDstFile) {
	while(fgets(line, sizeof line, srcFile) != NULL) {
	    //printf("%s",line);
	    if(strncmp(line,"A",1) == 0) {
		fprintf(aDstFile,"%s",line);
		ap += 1;
	    } else if (strncmp(line,"C",1) == 0) {
		fprintf(cDstFile,"%s",line);
		cp += 1;
	    } else if (strncmp(line,"D",1) == 0) {
		fprintf(dDstFile,"%s",line);
		dp += 1;
	    }
	}
	close(srcFile);
	close(aDstFile);
	close(cDstFile);
	close(dDstFile);
    }

    printf("A's processed: %d\n", ap);	
    printf("C's processed: %d\n", cp);
    printf("D's processed: %d\n", dp);

    return ap + cp + dp;
}
