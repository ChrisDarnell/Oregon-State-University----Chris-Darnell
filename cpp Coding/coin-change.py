import sys
import math


# Algorithm 1

def changeslow(coins, total):
    def changeslow_inner(coins, total, coins_used):
        if total == 0:
            return 0, [0] * len(coins)

        min_count = sys.maxint
        coins_used = [0] * len(coins)

        for i in range(0, len(coins)):

            if coins[i] <= total:
                recursive_result = changeslow_inner(coins, total - coins[i], coins_used)

                if recursive_result[0] + 1 < min_count:
                    min_count = recursive_result[0] + 1
                    recursive_result[1][i] += 1
                    coins_used = recursive_result[1]

        return min_count, coins_used

    results = changeslow_inner(coins, total, 0)

    return results[0], results[1]



# Algorithm 2

def changegreedy(coins, total):

    coins_used = [0] * len(coins)
    min_count = 0
    i = len(coins) - 1

    while total > 0:
    	if total >= coins[i]:
        	total = int(float((total - coins[i])
        	min_count += 1
        	coins_used[i] += 1
        else:
        	i -= 1
 
    return min_count, coins_used



# Algorithm 3

def changedp(coins, total):
    # Each index in min_count holds the minimum number of coins needed to reach index value
    min_count = [0] * (total + 1)

    # Each index in memo holds the last coin needed to reach index value
    memo = [0] * (total + 1)

    # Place optimal values in min_count and memo
    for i in range(1, total + 1):
        min_coins = i
        last_coin_used = 1

        for j in range(0, len(coins)):
            if coins[j] <= i:
                if min_count[i - coins[j]] + 1 < min_coins:
                    min_coins = min_count[i - coins[j]] + 1
                    last_coin_used = coins[j]

        min_count[i] = min_coins
        memo[i] = last_coin_used

    # Determine the number of each coin value used
    coins_used = [0] * len(coins)
    amt_left = total

    while amt_left > 0:
        coins_used[coins.index(memo[amt_left])] += 1
        amt_left -= memo[amt_left]

    return min_count[total], coins_used

# Name files

inputFilename = sys.argv[1]+".txt"
outputFilename = sys.argv[1]+"change.txt"


# File input

with open(inputFilename) as f:
    content = f.read().splitlines()


# Write over existing output file
target = open(outputFilename, 'w')
target.close()

# Write changeslow to file

# with open(outputFilename, "a") as target:
#     target.write('Algorithm Changeslow:\n')

# for i in range(0,len(content) - 1, 2):
#     coins = map(int, content[i].split())
#     cents = int(float((content[i + 1])
#     results = changeslow(coins, cents)

#     with open(outputFilename, "a") as target:
#         target.write(' '.join(map(str, coins)))
#         target.write("\n")
#         target.write(' '.join(map(str, results[1])))
#         target.write("\n")
#         target.write(str(results[0]))
#         target.write("\n")


# Write changegreedy to file

with open(outputFilename, "a") as target:
    target.write("\n")
    
with open(outputFilename, "a") as target:
    target.write('Algorithm Changegreedy:\n')

for i in range(0,len(content) - 1, 2):
    coins = map(int, content[i].split())
    cents = int(float((content[i + 1])
    results = changegreedy(coins, cents)

    with open(outputFilename, "a") as target:
        target.write(' '.join(map(str, coins)))
        target.write("\n")
        target.write(' '.join(map(str, results[1])))
        target.write("\n")
        target.write(str(results[0]))
        target.write("\n")


# Write changedp to file

with open(outputFilename, "a") as target:
    target.write("\n")

with open(outputFilename, "a") as target:
    target.write('Algorithm Changedp:\n')

for i in range(0,len(content) - 1, 2):
    coins = map(int, content[i].split())
    cents = int(float((content[i + 1])
    results = changedp(coins, cents)

    with open(outputFilename, "a") as target:
        target.write(' '.join(map(str, coins)))
        target.write("\n")
        target.write(' '.join(map(str, results[1])))
        target.write("\n")
        target.write(str(results[0]))
        target.write("\n")








