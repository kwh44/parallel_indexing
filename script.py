import sys
import subprocess
import glob
import os

if __name__ == '__main__':
    # check number of arguments
    if len(sys.argv) != 3:
        raise TypeError('Invalid number of arguments provided.\nPlease specify configuration file and number of runs.')

    number_of_runs = int(sys.argv[2])
    configuration_file = sys.argv[1]
    executable = './**/parallel_indexing.exe' if os.name == 'nt' else './**/parallel_indexing'

    with open(configuration_file, "r") as file:
        config = file.read().split("\n")
        output_alphabet, output_count = glob.glob(config[1].split("/")[-1])[0], glob.glob(config[2].split("/")[-1])[0]

    output = subprocess.run([glob.glob(executable)[0], configuration_file], stdout=subprocess.PIPE).stdout.decode(
        'utf-8')
    with open(output_alphabet, "r") as file:
        results = file.read()

    message = "The results are the same"

    # run methods some amount of times
    res = [[] for i in range(3)]
    for j in range(len(res)):
        for i in range(number_of_runs):
            output = subprocess.run([glob.glob(executable)[0], configuration_file],
                                    stdout=subprocess.PIPE).stdout.decode('utf-8')

            # get time of method by parsing output of program
            res[0].append(float(output.split("Total time: ")[1].split()[0]))
            res[1].append(float(output.split("Reading time: ")[1].split()[0]))
            res[2].append(float(output.split("Counting time: ")[1].split()[0]))

            with open(output_alphabet, "r") as file:
                local_results = file.read()

            if local_results != results:
                message = "The results are not the same"

    # print results and comparisons
    print("Converting string to double, microseconds:\n")
    print("Total time:\t", min(res[0]))
    print("Reading time:\t", min(res[1]))
    print("Counting time:\t", min(res[2]))
    print()
    print(message)
