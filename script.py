import subprocess
import matplotlib.pyplot as plt
import pandas as pd
import os.path

def plot():
    name_csv = "sample_result.csv"
    csv = pd.read_csv(name_csv, delimiter=',')
    X_values = csv["x"]
    Y_values = csv["y"]
    plt.figure(figsize=(10,10))
    plt.axis([0, 1, 0, 1])
    f = open('params.txt','r')
    # format: <name_gen> <num_pixel> <spp>
    params = f.readline().split()
    plt.title(f"{params[0]} (SPP: {params[2]} Pixel №: {int(params[1])})")
    f.close()
    plt.xlabel(f"dimension {params[3]}")
    plt.ylabel(f"dimension {params[4]}")
    plt.grid(True)
    plt.plot(X_values, Y_values, 'ro')
    plt.savefig("result_dim" + params[3] + "-" + params[4] + "_spp" + params[2] + "_pix" + \
                 params[1] + ".png")


if not os.path.exists("sampler-generators"):
    program = "g++ -std=c++17 -o sampler-generators main.cpp halton.cpp sobol.cpp scramble.cpp random.cpp sampler.cpp"

    process = subprocess.Popen(program, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    output, error = process.communicate()

    if process.returncode != 0:
        print('Произошла ошибка при компиляции программы:')
        print(error.decode())
    else:
        print("Программа скомпилирована")

"""
    Arguments:
    "w, width", "screen width"
    "h, height", "screen height"
    "spp", "samples per pixel"
    "pixelX", "pixel horizontal position"
    "pixelY", "pixel vertical position"
    "dimX", "dimension to output as x"
    "dimY", "dimension to output as y"
    "gen_type", "type of random generator"
    "scramble", "scrambling"
"""

args = ['--gen_type 2', '--spp 256', '--pixelX 10', '--pixelY 10', '--dimX 0', '--dimY 1', '--scramble 1']

execution_command = "./sampler-generators " + " ".join(str(arg) for arg in args)
print(execution_command)

execute_process = subprocess.Popen(execution_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
execute_output, execute_error = execute_process.communicate()

if execute_process.returncode == 0:
    plot()
else:
    print('Произошла ошибка при выполнении программы:')
    print(execute_error.decode())