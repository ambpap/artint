numb = []
summ = [0]*10
summ_i = 0

with open("artint6000.txt", "r") as file:
    for line in file: 
        content = line.strip()
        if content == "":
            continue
        elif content == "x":
            index = 10
        elif len(content) > 1 and content[1] == "0":
            index = 10
        else:
            index = int(content[0])
        
        numb.append(index)
        summ[index-1] +=1
        summ_i += 1

for x in numb:
	print(x,end = ' ')

print("\n")
	
szam = 0
for x in summ:
    szam+=1
    print(szam,"\t",x,"\t",round(x/summ_i*100,2),"%")
    
print("összesen: ",summ_i)

	
	
	

