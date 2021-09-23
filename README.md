# pwcheck

## School project (Introduction to Programming Systems, C)
Evaluation: TBA

# EN

The goal of the project is to create a program that receives a set of passwords at the input and checks each of them against all (fixed) necessary rules. Passwords that have been verified will be displayed, the rest will be discarded. Input data (password list) will be read from standard input (stdin), output data (filtered password list) will be printed to standard output (stdout).

## Compile

`gcc -std=c99 -Wall -Wextra -Werror pwcheck.c -o pwcheck`

## Execution syntax

`./pwcheck LEVEL PARAM [--stats]`

| Command | Description |
| --- | --- |
| `LEVEL` | An integer in the interval [1, 4] that specifies the required security level (see below) |
| `PARAM` | A positive integer that specifies an additional rule parameter (see below) |
| `--stats` | If specified, determines whether summary statistics of the analyzed passwords should be displayed at the end of the program |

## Security levels (controlled rules)

A total of 4 security levels are defined, expressed using 4 rules. The security level specifies that passwords must comply with all rules at that and lower levels. Ie. for example, security level 3 specifies that passwords must comply with rules 1, 2, and 3.

Some rules are parameterizable by an integer specified using the PARAM program argument. In the following list, this parameter is marked as X.

## List of rules

1. The password contains at least 1 uppercase and 1 lowercase letter.
2. The password contains characters from at least X groups. The groups considered are:
    - lowercase letters (a-z)
    - uppercase letters (A-Z)
    - numbers (0-9)
    - special characters (at least non-alphanumeric characters from the ASCII table in positions 33-126 must be supported)
3. The password does not contain the same sequence of characters of at least X.
4. The password does not contain two identical substrings of at least X.

## Statistics

If the specified argument is the --stats program, the program must print total statistics at the end of the output in the format:

```
Statistics:
Different characters: NCHARS
Minimum length: MIN
Average length: AVG
```

| Argument | Description |
| --- | --- |
| `NCHARS` | The number of different characters that appear across all passwords. |
| `MIN` | Length of the shortest password (or passwords). |
| `AVG` | Average length of the password (arithmetic mean) rounded to 1 decimal place. |

## Implementation details

### Input data (password list)

The list of passwords is passed to the program on standard input (stdin). Each password is entered on a separate line and contains only ASCII text data, except for the newline character. The maximum length of the password is 100 characters, otherwise it is invalid data. The program must support an unlimited number of passwords on entry.

### Program output

The standard output program (stdout) prints passwords from the input list, each on a separate line, that meet the required security level specified as the LEVEL program argument. Passwords must be listed without change and in the same order as they appeared on the entry.

After the output list of passwords, the program optionally lists statistics.


# CZ

Cílem projektu je vytvořit program, který na vstupu dostane sadu hesel a pro každé z nich ověří, jestli heslo splňuje všechna (pevně zadaná) požadovaná pravidla. Ta hesla, která projdou kontrolou, budou vypisována na výstup, ostatní budou zahozena. Vstupní data (seznam hesel) budou čtena ze standardního vstupu (stdin), výstup (filtrovaný seznam hesel) bude tisknut na standardní výstup (stdout).

## Překlad zdrojového souboru:

`gcc -std=c99 -Wall -Wextra -Werror pwcheck.c -o pwcheck`

## Syntax spuštění

`./pwcheck LEVEL PARAM [--stats]`

| Příkaz | Popis |
| --- | --- |
| `LEVEL` | Celé číslo v intervalu [1, 4], které určuje požadovanou úroveň bezpečnosti (viz níže) |
| `PARAM` | Kladné celé číslo, které určuje dodatečný parametr pravidel (viz níže) |
| `--stats` | Pokud je zadané, určuje, zda se na konci programu mají vypsat souhrnné statistiky analyzovaných hesel |

## Úrovně bezpečnosti (kontrolovaná pravidla)

Jsou definovány celkem 4 úrovně bezpečnosti vyjádřeny pomocí 4 pravidel. Úroveň bezpečnosti určuje, že hesla musí splňovat všechna pravidla na dané a nižší úrovni. Tzn. např. úroveň bezpečnosti 3 specifikuje, že hesla musí splňovat pravidla 1, 2 a 3.

Některá pravidla jsou parametrizovatelná celým číslem zadaným pomocí argumentu programu PARAM. V následujícím seznamu je tento parametr označen jako X.

## Seznam pravidel:

1. Heslo obsahuje alespoň 1 velké a 1 malé písmeno.
2. Heslo obsahuje znaky z alespoň X skupin. Uvažované skupiny jsou:
    - malá písmena (a-z)
    - velká písmena (A-Z)
    - čísla (0-9)
    - speciální znaky (podporované musí být alespoň nealfanumerické znaky z ASCII tabulky na pozicích 33-126)
3. Heslo neobsahuje sekvenci stejných znaků délky alespoň X.
4. Heslo neobsahuje dva stejné podřetězce délky alespoň X.

## Statistiky

Pokud je zadaný argument programu --stats, program musí na konec výstupu vypsat celkové statistiky ve formátu:
```
Statistics:
Different characters: NCHARS
Minimum length: MIN
Average length: AVG
```
| Proměnná | Popis |
| --- | --- |
| `NCHARS` | Počet různých znaků vyskytujících se napříč všemi hesly. |
| `MIN` | délka nejkratšího hesla (resp. hesel) |
| `AVG` | průměrná délka hesla (aritmetický průměr) zaokrouhlená na 1 desetiné místo. |

## Implementační detaily

### Vstupní data (seznam hesel)

Seznam hesel je programu předán na standardním vstupu (stdin). Každé heslo je zadáno na samostatném řádku a obsahuje pouze ASCII textová data, kromě znaku nového řádku. Maximální délka hesla je 100 znaků, jinak se jedná o nevalidní data. Program musí podporovat neomezený počet hesel na vstupu.

### Výstup programu

Program na standardní výstup (stdout) vypisuje hesla ze vstupního seznamu, každé na samostatný řádek, která splňují požadovanou úroveň bezpečnosti zadanou jako argument programu LEVEL. Hesla musí být vypsána beze změny a ve stejném pořadí jako se objevila na vstupu.

Za výstupním seznamem hesel pak program volitelně vypisuje statistiku.