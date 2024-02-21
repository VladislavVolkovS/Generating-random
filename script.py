import subprocess
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os.path

def plot():
    name_csv = "sample_result.csv"
    csv = pd.read_csv(name_csv, delimiter=',')
    X_values = csv["x"]
    Y_values = csv["y"]
    plt.figure(figsize=(10,10))
    plt.axis([0, 1, 0, 1])
    f = open('pix_num.txt','r')
    plt.title(f"Pixel: {int(f.readline())}")
    f.close()
    plt.xlabel("dimension X")
    plt.ylabel("dimension Y")
    plt.grid(True)
    plt.plot(X_values, Y_values, 'ro')
    plt.savefig("result.png")

if not os.path.exists("sampler-generators"):
    program = "g++ -o sampler-generators main.cpp halton.cpp sobol.cpp scramble.cpp random.cpp sampler.cpp"

    process = subprocess.Popen(program, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    output, error = process.communicate()

    if process.returncode != 0:
        print('Произошла ошибка при компиляции программы:')
        print(error.decode())


args = ['--gen_type 1', '--spp 8', '--pixelX 5', '--pixelY 5']

execution_command = "./sampler-generators " + " ".join(str(arg) for arg in args)
execute_process = subprocess.Popen(execution_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
execute_output, execute_error = execute_process.communicate()

if execute_process.returncode == 0:
    plot()
else:
    print('Произошла ошибка при выполнении программы:')
    print(execute_error.decode())