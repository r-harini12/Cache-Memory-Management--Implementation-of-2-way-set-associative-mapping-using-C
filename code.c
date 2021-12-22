#include<stdio.h>
#include<stdlib.h>
#define mm 128
#define set 4
#define line 2

// implementation of 2 way set associative cache memory management using lru(least recently used) mechanism
int main() {
    int **cache,*lru,ch,addr,s,nh=0,nm=0;
    /*  cache - 2D cache memory block(sets*lines)
        lru - to keep track of least recently used element in each set(index values).
        ch - choice
        addr -  main memory address to be retrieved
        s - set number (addr%set)
        nh - number of hits
        nm - number of misses
        number of cache memory accesses = nh+nm
    */
    float hr,mr;        //hit and miss ratio
    lru=(int *)malloc(sizeof(int)*set);
    cache=(int **)malloc(sizeof(int *)*set);
    for(int i=0;i<set;i++) {
        cache[i]=(int *)malloc(sizeof(int)*line);
    }
    // intialization of cache memory with -1.
    for(int i=0;i<set;i++) {
        for(int j=0;j<line;j++){
            cache[i][j]=-1;
        }
    }
    printf("**size of main memory is %d(address between 0 and %d inclusive**\n",mm,mm-1);
    //printf("**enter -1 to exit!!**\n");
    printf("1. retrieving the memory location\n");
    printf("2. print the cache memory block\n");
    printf("3. print hit and miss ratio\n");
    printf("4. exit\n");
    
    while(1) {
        printf("\n");
        printf("enter choice : ");
        scanf("%d",&ch);
        while(!(ch>0 && ch<5)){
            printf("invalid choice .enter again : ");
            scanf("%d",&ch);
        };
        if(ch==1) {
            printf("enter main memory address to retrive : ");
            scanf("%d",&addr);
            while(!(addr>=0 && addr<mm)){
                printf("invalid address. enter again : ");
                scanf("%d",&addr);
            };
            s=addr%set;     // set has been calculated.
            int l=0;        // flag to see if its hit(1) or miss(0)
            for(int i=0;i<line;i++) {
                if(cache[s][i]==addr) {
                    //incase of hit
                    nh++;
                    l=1;    //flag is set
                    if(cache[s][1]==-1) lru[s]=1;
                    else lru[s]=0;
                    printf("*hit*\n"); 
                    if(i==0 && cache[s][1]!=-1) {
                        /*int temp;
                        temp=cache[s][0];
                        cache[s][0]=cache[s][1];
                        cache[s][1]=temp;*/
                        lru[s]=1;
                        //printf("%d %d\n",cache[s][0],cache[s][1]);
                        break;
                    }
                    printf("set %d : %d %d\n",s,cache[s][0],cache[s][1]);
                }
            }
            if(l==0) {
                // incase of miss
                printf("**miss**\n");
                if(cache[s][0]==-1) {
                    cache[s][0]=addr;
                    nm++;
                    lru[s]=1;
                    printf("set %d : %d %d\n",s,cache[s][0],cache[s][1]);
                }
                else if(cache[s][1]==-1){
                    cache[s][1]=addr;
                    nm++;
                    lru[s]=0;
                    printf("set %d : %d %d\n",s,cache[s][0],cache[s][1]);
                }    
                else {
                    //cache[s][0]=cache[s][1];
                    if(lru[s]==0) {
                        cache[s][0]=addr;
                        lru[s]=1;
                    }
                    else if(lru[s]==1) {
                        cache[s][1]=addr;
                        lru[s]=0;
                    }
                    nm++;
                    printf("set %d : %d %d\n",s,cache[s][0],cache[s][1]);
                }
            }
            printf("miss : %d   hit : %d\n",nm,nh);
        }
        if(ch==2) {
            printf("**cache memory block**\n");
            for(int i=0;i<set;i++) {
                for(int j=0;j<line;j++){
                    printf("%d\t",cache[i][j]);
                }
                printf("\n");
            }
        }
        if(ch==3) {
            if(nh==0 && nm==0) printf("no retrievals done to calculate hit and miss ratios\n");
            else {
                hr=nh*1.00000000/(nh+nm);
                mr=nm*1.00000000/(nh+nm);
                printf("hit ratio : %f\n",hr);
                printf("miss ratio : %f\n",mr);
            }
        }
        if(ch==4)  {
            exit(0);
        }
    }
}
