import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
//Тестировка инициализации
        System.out.println("Test of initialization:") ;
        double testArr[] = new double[8];
        for (int i = 0; i < testArr.length; i++)
            testArr[i] = Math.random() * 50;
        Vector elem1 = new Vector();
        Vector elem2 = new Vector(13);
        Vector elem3 = new Vector(testArr);
//Распечатка после инициализации
        printAllElement(elem1,elem2,elem3);
//Тестировка вставки
        System.out.println("Test of insert:");
        for (int i = 1; i < 13; i++) {
            elem1.insert(Math.random() * 25, i);
            elem2.insert(Math.random() * 25, i);
            elem3.insert(Math.random() * 25, i);
        }
        printAllElement(elem1,elem2,elem3);
//Тестировка удаления
        System.out.println("Test of erase:");
        for (int i = 0; i < 5; i++) {
            elem1.erase(i);
            elem2.erase(i);
            elem3.erase(i);
        }
        printAllElement(elem1,elem2,elem3);
//Тестировка установки
        System.out.println("Test of set:");
        for (int i = 1; i < 6; i++) {
            elem1.set(i , Math.random() * 15);
            elem2.set(i , Math.random() * 15);
            elem3.set(i , Math.random() * 15);
        }
        printAllElement(elem1,elem2,elem3);
//Тестировка взятия
        System.out.println("Test of get:");
        System.out.println("\t\t1\t\t\t\t\t2\t\t\t\t\t3");
        for (int i = 1; i < elem1.getSize(); i++) {
            System.out.println(elem1.get(i) + "  " + elem2.get(i) + "  " + elem3.get(i));
        }
//Тестировка клонирования
        System.out.println("Test of clone:");
        testArr=elem1.cloneArr();
        for(int i=0;i<testArr.length;i++)
            System.out.print(testArr[i]+"  ");
        System.out.println();

//Тестировка очистки
        System.out.println("Test of clean:");
        elem1.clear();
        elem1.print();
    }

    static void printAllElement(Vector elem1,Vector elem2,Vector elem3){
        System.out.print("1 element:");
        elem1.print();
        System.out.print("2 element:");
        elem2.print();
        System.out.print("3 element:");
        elem3.print();
    }
}

class Vector {
    private double arr[];
    private int size = 0;
    private double newArr[];

    Vector() {
        arr = new double[10];
    }

    Vector(int capacity) {
        arr = new double[capacity];
    }

    Vector(double[] arr) {
        size = arr.length;
        this.arr = Arrays.copyOf(arr, arr.length + 10);
    }

    void print() {
        if (size == 0) {
            System.out.println("The array is empty!");
        } else {
            for (int i = 0; i < size; i++)
                System.out.print(arr[i] + "  ");
            System.out.println();
        }
    }

    int getSize() {
        return size;
    }

    void clear() {
        size = 0;
    }

    double get(int pos) {
        if (pos <= 0 || pos > size) {
            System.out.println("This element is not exist!");
            return 0;
        } else {
            return arr[pos - 1];
        }
    }

    void set(int pos, double val) {
        if (pos <= 0 || pos > size) {
            System.out.println("This position is not correct!");
        } else {
            arr[pos - 1] = val;
        }
    }

    void insert(double val, int pos) {
        if (size >= (arr.length - 1)) {
            newArr = Arrays.copyOf(arr, arr.length + 10);
            arr = newArr;
        }
        if ((pos-1 > size) || (pos < 1)) {
            System.out.println("Given position is incorrect! Try again!");
        } else {
            for (int i = size; i > (pos - 1); i--)
                arr[i] = arr[i - 1];
            arr[pos - 1] = val;
            size++;
        }
    }

    void erase(int pos) {
        if ((pos - 1 > size) || (pos < 1)) {
            System.out.println("Given position is incorrect! Try again!");
        } else {
            for (int i = pos - 1; i < size - 2; i++)
                arr[i] = arr[i + 1];
            size--;
        }
    }

    double[] cloneArr() {
        newArr=new double[size];
        System.arraycopy(arr,0,newArr,0,size);
        return newArr;
    }
}
