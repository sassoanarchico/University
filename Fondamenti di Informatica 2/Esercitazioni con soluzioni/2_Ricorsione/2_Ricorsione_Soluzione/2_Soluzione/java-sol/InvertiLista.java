
import java.util.*; 

public class InvertiLista {
	
	public static void invertiLista(LinkedList<Integer> list) {
		if(list.size() > 1) {
			//ci sono almeno 2 elementi
			Integer head = list.pop();
			invertiLista(list);
			list.addLast(head);
		}
	}
}



