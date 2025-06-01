numb = []
summ = [0] * 10
summ_i = 0

with open("training_data_raw.txt", "r") as file:
    line = file.readline()
    content = line.strip().split()

    for item in content:
        if item == "":
            continue
        elif len(item) > 1 and item[1] == "0":
            index = 10
        else:
            index = int(item[0])

        numb.append(index)
        summ[index - 1] += 1
        summ_i += 1

print("\n")

szam = 0
for x in summ:
    szam += 1
    print(szam, "\t", x, "\t", round(x / summ_i * 100, 2), "%")
    
print("összesen: ", summ_i)


#2
prev = [[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0]]
p = 1
for n in numb:
    prev[p-1][n-1] += 1
    p = n

index = 0
for x in prev:
    index += 1
    print(index,":")
    ind = 0
    for h in x:
        ind+=1
        print("\t",ind,"\t",h)
        



