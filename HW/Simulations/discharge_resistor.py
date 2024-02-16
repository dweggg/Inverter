import itertools
import math

# Given data
target_resistance = 20000  # 18kΩ
tolerance = 1000  # ±1kΩ
power_rating = 20  # 20W
voltage = 600  # 600V
capacitance = 100e-6  # 100uF
Vf = 60  # 60V

# E-12 resistor values in Ω
e12_values = [1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2]
multipliers = [10 ** x for x in range(6)]

# SMD packages with their corresponding wattage
smd_packages = {
    "1206": 0.25,
    "1210": 0.5,
    "2010": 0.75,
    "2512": 1
}


# combination = [value, number of parallel resistors]

def calculate_resistance(combination):
    return combination[0] / combination[1]


def calculate_power_dissipation(combination):
    power_dissipation = voltage ** 2 / combination[0]
    return power_dissipation


def calculate_discharge_time(combination):
    resistance = calculate_resistance(combination)
    discharge_time = resistance * capacitance * math.log(voltage / Vf)
    return discharge_time


def find_parallel_combinations(target_resistance, tolerance, power_rating):
    all_combinations = []
    for r_value in e12_values:
        for multiplier in multipliers:
            base_resistance = r_value * multiplier
            for num_parallel in range(1, 101):  # Assuming a maximum of 100 parallel resistors
                current_resistance = base_resistance / num_parallel
                if target_resistance - tolerance <= current_resistance <= target_resistance + tolerance:
                    for package, wattage in smd_packages.items():
                        power_dissipation = calculate_power_dissipation([base_resistance, num_parallel])
                        if power_dissipation <= wattage:
                            discharge_time = calculate_discharge_time([base_resistance, num_parallel])
                            power_percentage = (power_dissipation / wattage) * 100
                            all_combinations.append((base_resistance, num_parallel, package, power_dissipation, discharge_time, power_percentage))
    return all_combinations


if __name__ == "__main__":
    combinations = find_parallel_combinations(target_resistance, tolerance, power_rating)
    print("Possible combinations:")
    for combo in combinations:
        print(f"Resistance: {round(combo[0]/1000)}kΩ, n: {combo[1]}, SMD Package: {combo[2]}, "
              f"P_diss: {round(combo[3], 3)} W, t_dis: {round(combo[4], 3)} s, "
              f"Power: {round(combo[5], 2)}% of package maximum")
