#include<stdio.h>
int main(){
int i,n,a[100],even=0,odd=0;

printf("Enter the number you want to find :\n");
scanf("%d",&n);

for(i=0; i<n;i++){
    scanf("%d",&a[i]);
}
for(i=0;i<n;i++){
    if(a[i] % 2 == 0){
      even++;
    }
    else odd++;
}

printf("Even %d\n",even);
printf("Odd %d\n",odd);
return 0;
}
