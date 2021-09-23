# pwcheck

## School project (Introduction to Programming Systems, C)
Evaluation: TBA

# EN

# CZ

Cílem projektu je vytvořit program, který na vstupu dostane sadu hesel a pro každé z nich ověří, jestli heslo splňuje všechna (pevně zadaná) požadovaná pravidla. Ta hesla, která projdou kontrolou, budou vypisována na výstup, ostatní budou zahozena. Program implementujte ve zdrojovém souboru "pwcheck.c". Vstupní data (seznam hesel) budou čtena ze standardního vstupu (stdin), výstup (filtrovaný seznam hesel) bude tisknut na standardní výstup (stdout).

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
2. Heslo obsajuje znaky z alespoň X skupin. Uvažované skupiny jsou:
   - malá písmena (a-z)
   - velká písmena (A-Z)
   - čísla (0-9)
   - speciální znaky (podporované musí být alespoň nealfanumerické znaky z ASCII tabulky na pozicích 33-126)
3. Heslo neobsahuje sekvenci stejných znaků délky alespoň X.
4. Heslo neobsahuje dva stejné podřetězce délky alespoň X.

## Statistiky

Pokud je zadaný argument programu --stats, program musí na konec výstupu vypsat celkové statistiky ve formátu:
```
Statistika:
Ruznych znaku: NCHARS
Minimalni delka: MIN
Prumerna delka: AVG
```
kde
| --- | --- |
| `NCHARS` | Počet různých znaků vyskytujících se napříč všemi hesly. |
| `MIN` | délka nejkratšího hesla (resp. hesel) |
| `AVG` | průměrná délka hesla (aritmetický průměr) zaokrouhlená na 1 desetiné místo. |