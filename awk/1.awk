BEGIN{
print "incepem"
}

{
print $1,($2+$3)/2
sum=sum+($2+$3)/2
contor++
}

END{
print "media="sum/contor
}
