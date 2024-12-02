import csv
import matplotlib.pyplot as plt
import numpy as np

filename = "DATA.csv"

def readData(n, h, tree):
     with open(filename, "r") as r_file:
        reader = csv.DictReader(r_file, delimiter=";")  # Чтение данных из DATA
        for row in reader:
            
            if(row["Tree"] == tree):
                n.append(int(row["n"]))
                h.append(int(row["h(n)"]))
     
def pracGraphics():
    
    #BST
    plt.xlabel("n")
    plt.ylabel("h(n)")
    n, h = [], []
    readData(n, h, "BST")
    plt.scatter(n, h, label="BST")
    reg(n, h, "blue", 1)
    plt.legend()
    plt.savefig("Graphics\BST.png")
    #AVL
    plt.clf()
    plt.xlabel("n")
    plt.ylabel("h(n)")
    n.clear()
    h.clear()
    readData(n, h, "AVL")
    plt.scatter(n, h, label="AVL")
    reg(n, h, "blue", 1)
    plt.legend()
    plt.savefig("Graphics\AVL.png")
    #RB

    #ALL
    plt.clf()
    plt.xlabel("n")
    plt.ylabel("h(n)")
    n1, n2, h1, h2 = [], [], [], []
    readData(n1, h1, "BST")
    readData(n2, h2, "AVL")
    plt.scatter(n1, h1, label="BST")
    reg(n1, h1, "blue", 1)
    plt.scatter(n2, h2, label="AVL")
    reg(n2, h2, "orange", 2)
    plt.legend()
    plt.savefig("Graphics\ALL.png")

def reg(n, h, col, index):
    # Находим коэффициенты регрессии 2-й степени
    coefficients = np.polyfit(n, h, 2)
    polynomial_regression = np.poly1d(coefficients)


    # Генерация значений для кривой регрессии
    x_reg = np.linspace(min(n), max(n), 100)
    y_reg = polynomial_regression(x_reg)

    # Построение кривой регрессии
    plt.plot(x_reg, y_reg, color=col)


    a, b, c = coefficients
    

    # Выводим уравнение в правом верхнем углу с небольшим смещением
    # Сдвигаем уравнение по вертикали с учетом порядка кривой
    plt.text(0.95,  0.2 - 0.05 * index, f"y = ({a:.2e})n^2 + ({b:.2e})n + ({c:.2e})", transform=plt.gca().transAxes,
             fontsize=10, color=col, ha='right', va='top')

     


pracGraphics()



