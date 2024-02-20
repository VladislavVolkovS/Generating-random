import subprocess

program = "g++ -o sampler-generators main.cpp halton.cpp sobol.cpp scramble.cpp random.cpp sampler.cpp"

args = ['--gen_type 1', '--spp 8']

process = subprocess.Popen([program] + args, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

output, error = process.communicate()

if process.returncode != 0:
    print('Произошла ошибка при компиляции программы:')
    print(error.decode())


execution_command = "./sampler-generators " + " ".join(str(arg) for arg in args)
execute_process = subprocess.Popen(execution_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
execute_output, execute_error = execute_process.communicate()

if execute_process.returncode == 0:
    print(execute_output.decode())
else:
    print('Произошла ошибка при выполнении программы:')
    print(execute_error.decode())