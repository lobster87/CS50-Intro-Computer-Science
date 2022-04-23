# TODO
def main():
    # take in text
    switch = True
    while switch == True:
        try:
            text = input("Text: ")
            switch = False
        except:
            pass

    # calculate number of characters, sentences spaces and words
    characters = 0
    sentences = 0
    spaces = 0
    words = 0

    for letter in text:
        letter = ord(letter)
        if (letter >=97 and letter <=122) or (letter>=65 and letter <=90):
            characters += 1
        elif letter == 33 or letter == 46 or letter == 63:
            sentences += 1
        elif letter == 32:
            spaces += 1

    words = spaces + 1

    # calculate L and S for coleman-Liau index formula
    L = (characters/words)*100
    S = (sentences/words)*100

    # coleman-liau index formula
    index = round((0.0588 * L) - (0.296 * S) - 15.8)

    # print index
    if index < 1:
        print("Before Grade 1")
    elif index < 16:
        print(f"Grade {index}")
    else:
        print("Grade 16+")

if __name__ == '__main__':
    main()