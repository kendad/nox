function MathStuff(a,b)
	print("[LUA] MathStuff("..a..","..b..")")
	return (a*a)+b
end

function changeTime(time)
	print("[LUA] changeTime called "..time.."")
end

for i=0,1,1
do
	c=HostSum(i,i+1)
	print(c)
end