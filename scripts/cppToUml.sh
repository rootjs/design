#!/bin/sh
sed 's/static //g' $1 | sed 's/inline//g' | sed 's/<\s/</g' | \
sed 's/\s>/\>/g' |  awk '{t=$1;$1=$(NF+1);$(NF+1)=t}1' | sed 's/ /+/' \
 | awk '{$NF=": "$NF}1' | sed 's/\/\*\s//g' | \
sed 's/\s\*\///g' | sed 's/const\s//g' | sed 's/^/  /' | \
sed -r 's/\(\s/\(/g'| sed -r 's/\s\)/\)/g' | \
sed 's/\s:/:/g' | \
sed 's/\,//g' | \
awk '{
c=2;
if (NF==6)
{ 
    t=$c;
    $c=$(c+1)":";
    $(c+1)=t;
}
else if (NF==8)
{
    t=$c;
    $c=$(c+1)":";
    $(c+1)=t",";
    
    c+=2
    
    t=$c;
    $c=$(c+1)":";
    $(c+1)=t;
}
else if (NF==10)
{
    t=$c;
    $c=$(c+1)":";
    $(c+1)=t",";
    
    c+=2

    t=$c;
    $c=$(c+1)":";
    $(c+1)=t",";
    
    c+=2
    
    t=$c;
    $c=$(c+1)":";
    $(c+1)=t;
}
else if (NF==12)
{
    t=$c;
    $c=$(c+1)":";
    $(c+1)=t",";
    
    c+=2

    t=$c;
    $c=$(c+1)":";
    $(c+1)=t",";
    
    c+=2

    t=$c;
    $c=$(c+1)":";
    $(c+1)=t",";
    
    c+=2
    
    t=$c;
    $c=$(c+1)":";
    $(c+1)=t;
}
else if (NF==14)
{
    t=$c;
    $c=$(c+1)":";
    $(c+1)=t",";
    
    c+=2
    
    t=$c;
    $c=$(c+1)":";
    $(c+1)=t",";
    
    c+=2

    t=$c;
    $c=$(c+1)":";
    $(c+1)=t",";
    
    c+=2

    t=$c;
    $c=$(c+1)":";
    $(c+1)=t",";
    
    c+=2
    
    t=$c;
    $c=$(c+1)":";
    $(c+1)=t;
}
}1' \
  > $2


