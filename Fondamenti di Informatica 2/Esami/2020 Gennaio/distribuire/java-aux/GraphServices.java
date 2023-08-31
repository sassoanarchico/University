import java.util.*;

public class GraphServices {


	public static <V> void bfs(Graph<V> g, Node<V> source) {
		StringBuilder sb = new StringBuilder();
		sb.append("BFS da " + source.getElement() + ":\n");
		Queue<Node<V>> q = new LinkedList<>();
		source.timestamp = 0;
		source.stato = Node.Stato.EXPLORED;
		q.add(source);
		while(!q.isEmpty()) {
			Node<V> v = q.remove();
			for (Edge<V> e: g.getOutEdges(v)) {
				Node<V> u = e.getTarget();
				if (u.stato == Node.Stato.UNEXPLORED) {
					u.timestamp = v.timestamp +1;
					u.stato = Node.Stato.EXPLORED;
					q.add(u);
					
					
				}
			}
			sb.append("Livello " +v.getElement() + ": " +v.timestamp + "\n");
			
		}
		System.out.println(sb);
	}

	public static <V> String sssp(Graph<V> g, Node<V> source) {
		StringBuilder sb = new StringBuilder();
		sb.append("Distanza dal nodo " + source.getElement() + " [");
		
		MinHeap<Node<V>> pq = new MinHeap<>();
		Map<Node<V>, HeapEntry<Node<V>>> pqTokens = new HashMap<>();
		for (Node<V> v: g.getNodes()) {
			if (v == source) v.timestamp = 0;
			else v.timestamp = 100000;
			pqTokens.put(v, pq.insert(v.timestamp, v));
		}

		while(!pq.isEmpty()) {
			HeapEntry<Node<V>> e1 = pq.removeMin();
			Node<V> v = e1.getValue();
			sb.append(v.getElement() + ":" +v.timestamp +", ");
			for (Edge<V> e: g.getOutEdges(v)) {
				Node<V> u = e.getTarget();
				int wg = e.getWeight();
				if (wg + v.timestamp < u.timestamp) {
					u.timestamp = wg + v.timestamp;
					pq.replaceKey(pqTokens.get(u), u.timestamp);
				}
			}
			
		}
		/*
		for (Node<V> n: g.getNodes()) {
			sb.append(n.getElement() + ":" +n.timestamp +", ");
		}
		*/
		sb.replace(sb.length() -2, sb.length(), "]");
		return sb.toString();
	}

	public static <V> void apsp(Graph<V> g) {
		for (Node<V> n: g.getNodes()) {
			System.out.println(sssp(g,n));
		}
	}
}
