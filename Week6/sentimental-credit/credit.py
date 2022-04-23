# TODO

def main():
    # enter card number and verify that it is a digit
    switch = True
    while switch == True:
        try:
            number = int(input("Give card number: "))
            switch = False
        except:
            pass

    # Amex (15 digits, starts with 34 or 37)
    if len(str(number)) == 15 and (
        int(str(number)[:2]) == 34 or
        int(str(number)[:2]) == 37):

        print('AMEX')

    # mastercard (16 digits, starts with 51,52,53,54,55)
    elif len(str(number)) == 16 and (
        int(str(number)[:2]) == 51 or
        int(str(number)[:2]) == 52 or
        int(str(number)[:2]) == 53 or
        int(str(number)[:2]) == 54 or
        int(str(number)[:2]) == 55):

        print('MASTERCARD')
    # visa (13 or 16 digits, starts with a 4)
    elif (len(str(number)) == 13 or len(str(number)) == 16) and int(str(number)[:1]) == 4:
        print('VISA')

    else:
        print('INVALID')

if __name__ == "__main__":
    main()