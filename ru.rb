

re = /^.* s=(\d+\.\d+).*t=(\d+\.\d+)/
co=0;
ARGF.each_line do |line|

if re.match(line)
printf "%s %s \n",$1,$2 ;
co=co+1
end
end
printf " this is the count %d" ,co;
