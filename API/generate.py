with open("voltages.txt", 'w') as file:
    for i in range (0, 2**8):
        file.write(i.__str__() + ' ' + (i * 250 / (2**8)).__str__() + '\n')
        ##file.write("{0:b}".format(i).zfill(8) + ' ' + (i * 250 / (2**8)).__str__() + '\n')