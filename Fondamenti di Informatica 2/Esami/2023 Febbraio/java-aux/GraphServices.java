import java.util.*;

public class GraphServices {

	public static <V> void kdist(Graph<V> g, Graph.GraphNode<V> source, int k) {
		g.resetStatus();
		LinkedList<Graph.GraphNode<V>> l = new LinkedList<>();
		source.timestamp = 0;
		l.add(source);
		System.out.print(source.value + " ");
		while(!l.isEmpty()) {
			Graph.GraphNode<V> n = l.removeFirst();
			n.state = Graph.GraphNode.Status.EXPLORED;
			for (Graph.GraphNode<V> ed: g.getOutNeighbors(n)) {
				if (ed.state ==  Graph.GraphNode.Status.UNEXPLORED) {
					ed.state = Graph.GraphNode.Status.EXPLORING;
					ed.timestamp = n.timestamp +1;
					l.add(ed);
					if (ed.timestamp <= k) {
						System.out.print(ed.value + " ");
					}
				}
				
			}
		}
	}

}


/*
 *	boolean isHeap(Tree T):
 * 		return isOk(T.root)
 * 
 * 	boolean isOk(Nodo v):
 * 		if v è foglia:  //v == null
 * 			return true;
 * 		if v.key > v.left || v.key > v.right
 * 			return false;
 * 		else return isOk(v.left) && isOk(v.right)
 * 	
 * ////////////// 	Q3 	
 * 
 * 	for (int i = 0; i < n1; i++):
 * 		for (int j = 0; j < n2; j++) 
 * 			if (l1[i] != l2[j])
 * 				inserisci l1[i] in l
 *			
 */