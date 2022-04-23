# TODO

# ask for height
tf = False
while tf == False:
    try:
        height = int(input("how high?"))
        if height > 0 and height < 9:
            tf=True
    except:
        pass

# make mario by row
for i in range(height):
    # initial spaces
    print(' '*(height-(i+1)), end="")
    # pyramid blocks on left
    print('#'*(i+1), end="")
    # middle spaces
    print(' '*2, end="")
    # pyramid blocks on right
    print('#'*(i+1))
