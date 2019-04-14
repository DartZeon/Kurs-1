
public class Vector {

	   private double[] arr = new double[10];
	   private int size = 0; // изначально - пусто
	   public void insert(double val, int pos){
	       if(все место занято){
	           //создать новый массив в 2 раза больше
	           //скопировать в него элементы
	         //  присвоить ссылку на него "старому" массиву arr
	       }//if
	       // собственно вставка:
	       //сдвинуть элементы от pos+1 до size-1 на 1 позицию вправо
	       //в позицию pos записать val
	       //увеличить size на 1
	   }//insert
	   public void print(){
	       // распечатать элементы в строку, разделяя пробелами
	   }
	   
	   Vector(){
		   size = 0;
		   arr = new double[10];
		   
	   }
	   
	   Vector(int capacity){
		   size = 0;
		   arr = new double[capacity];
		   
	   }
	   Vector(double[] arr){		   
		   size = arr.length;
		   this.arr = new double[size];
		   for(int i = 0; i < size; i++) {
			   this.arr[i] = arr[i];
		   }
	   }
	   
	   int getSize() {
		   return size;
	   }
	   
	   double get(int pos) {
		   
	   }
	   
	   void set(double val, int pos) {
		   
	   }
	   
	   void insert(double val, int pos) {
		   
	   }
	   
	   void erase(int pos) {
		   
	   }
	   
	   void clear() {
		   
	   }
	
	

}
