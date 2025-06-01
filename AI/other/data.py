numb = [0] * 10  

with open("artint6000.txt", "r") as file:
    for line in file: 
        content = line.strip()
        if content == "":
            continue
        elif content == "x":
            index = 9
        elif len(content) > 1 and content[1] == "0":
            index = 9
        else:
            index = int(content[0])-1
        
        numb[index] += 1

szam = 0
ossz = 0

for x in numb:
	szam += 1
	ossz += x
	print(szam,"\t",x)
	
print("összesen: ",ossz)

szam = 0

for x in numb:
	szam += 1
	print(szam,"\t",round(x/ossz*100,2),"%")
