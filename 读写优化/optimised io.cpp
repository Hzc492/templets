/*读写优化*/
void hin(int &res){
    char ch;
    bool flag=false;
    while (!isdigit(ch=getchar()))
        if (ch=='-') flag=true;
    for (res=ch-'0';isdigit(ch=getchar());res=res*10+ch-'0');
    if (flag) res=-res;
}
void hout(int x){
    if (x<0){
        putchar('-');
        x=-x;
    }
    if (x>9) hout(x/10);
    putchar(x%10+'0');
}
int main(){
    int n;
    hin(n);
    hout(n);
}
