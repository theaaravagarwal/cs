import sys as s
x,y,c,n=0,1,1,int(s.stdin.readline());
z=y;
s.stdout.write("0 1 ");
while c<=n:
    s.stdout.write("%s "%z);
    c+=1;
    x,y=y,z;
    z=x+y;
print();
