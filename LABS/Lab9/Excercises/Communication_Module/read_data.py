kernel_module = open('/proc/iytecommodule')

greeting = kernel_module.readline();

print(greeting)

kernel_module.close()
