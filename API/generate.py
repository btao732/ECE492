with open("voltages.txt", 'w') as file:
    for i in range (0, 2**8):
        vout = i * 250 / (2**8)
        file.write("{0:b}".format(i).zfill(8) + " = " + vout.__str__() + '\n')