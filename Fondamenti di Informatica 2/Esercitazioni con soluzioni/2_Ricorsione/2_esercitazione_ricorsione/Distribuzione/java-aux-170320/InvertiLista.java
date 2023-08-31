
import java.util.*;

public class InvertiLista {

	public static void invertiLista(LinkedList<Integer> list) {
		if (list.size()> 1) {
			Integer e = list.removeFirst();
			invertiLista(list);
			list.addFirst(e);
		}
	}
}
