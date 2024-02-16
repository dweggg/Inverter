import itertools

# Define resistor series and their respective multipliers
resistor_series = {
    'E6': [1.0, 1.5, 2.2, 3.3, 4.7, 6.8],
    'E12': [1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2],
    'E24': [1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0, 2.2, 2.4, 2.7, 3.0, 3.3, 3.6, 3.9, 4.3, 4.7, 5.1, 5.6, 6.2, 6.8, 7.5, 8.2, 9.1],
    'E48': [1.00, 1.05, 1.10, 1.15, 1.21, 1.27, 1.33, 1.40, 1.47, 1.54, 1.62, 1.69, 1.78, 1.87, 1.96, 2.05, 2.15, 2.26, 2.37, 2.49, 2.61, 2.74, 2.87, 3.01, 3.16, 3.32, 3.48, 3.65, 3.83, 4.02, 4.22, 4.42, 4.64, 4.87, 5.11, 5.36, 5.62, 5.90, 6.19, 6.49, 6.81, 7.15, 7.50, 7.87, 8.25, 8.66, 9.09],
}

# Define tolerance values
sum_tolerance = 10000  # 10k ohms
# Target values
target_sum = 100000  # 100k ohms

Vout = 4
Vout_error = 0.15

# Function to generate resistor values for a given series
def generate_resistor_values(series):
    return resistor_series[series]
# Function to calculate the closest combination
def find_closest_combination(Vout, Vout_error):
    closest_sum = None
    closest_combination = None
    lowest_series_combination = None
    comb_number = 0
    for series, values in resistor_series.items():
        for multiplier in values:
            resistor_values = generate_resistor_values(series)
            for combo in itertools.combinations(resistor_values, 2):
                R1, R2 = combo
                comb_number += 1
                
                sum_resistors = (R1 + R2) * 10000  # in ohms
                if Vout >  1.186 * 2:
                    actual_Vout = 1.186 * (1 + R2 / R1)
                else:
                    actual_Vout = 1.186 * (1 + R1 / R2)
                Vout_diff = Vout - actual_Vout

                # Check if the sum is within +/- 10kR and the Vout error is within the specified tolerance
                if ((target_sum - sum_tolerance) <= sum_resistors <= (target_sum + sum_tolerance)) and (Vout_diff <= Vout_error and Vout_diff > 0):
                    if closest_sum is None or abs(sum_resistors - target_sum) < abs(closest_sum - target_sum):
                        closest_sum = sum_resistors
                        if Vout >  1.186 * 2:
                            closest_combination = (series, R1, R2, actual_Vout)
                        else:
                            closest_combination = (series, R2, R1, actual_Vout)

                    if lowest_series_combination is None or series < lowest_series_combination[0]:
                        if Vout >  1.186 * 2:
                            lowest_series_combination = (series, R1, R2, actual_Vout)
                        else:
                            lowest_series_combination = (series, R2, R1, actual_Vout)

    return closest_combination, lowest_series_combination, comb_number



# Find the closest combination
closest_combination, lowest_series_combination, comb_number = find_closest_combination(Vout, Vout_error)

# Print the result
if closest_combination:
    series, R1, R2, actual_Vout = closest_combination
    print("Closest combination found:")
    print("Series:", series)
    print("R1 =", R1*10, "kOhms")
    print("R2 =", R2*10, "kOhms")
    print("Vout =", actual_Vout, "V")
else:
    print("No combination found within the specified Vout error.")

if lowest_series_combination:
    series, R1, R2, actual_Vout = lowest_series_combination
    print("Lowest series combination found:")
    print("Series:", series)
    print("R1 =", R1*10, "kOhms")
    print("R2 =", R2*10, "kOhms")
    print("Vout =", actual_Vout, "V")
else:
    print("No combination found using the lowest series.")

print("A total of ", comb_number, " combinations were checked")