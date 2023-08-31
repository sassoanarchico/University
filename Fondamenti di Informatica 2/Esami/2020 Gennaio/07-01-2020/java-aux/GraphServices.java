import java.util.*;

public class GraphServices {


	public static <V> void bfs(Graph<V> g, Node<V> source) {
		Queue<Node<V>> queue = new LinkedList<>();
		queue.add(source);
		source.timestamp = 0;
		while (!queue.isEmpty()) {
			Node<V> v = queue.poll();
			v.stato = Node.Stato.EXPLORED;
			for (Edge<V> e : g.graph.get(v)) {
				Node<V> u = e.getTarget();
				if (u.stato == Node.Stato.UNEXPLORED) {
					u.stato = Node.Stato.EXPLORING;
					u.timestamp = v.timestamp + 1;
					queue.add(u);
				}
			}
			System.out.println("Livello " + v.getElement() + ": " + v.timestamp);
		}
	}

	// Distanze dal nodo c [a:100000, b:100000, d:2, c:0, e:1, f:3]

	public static <V> String sssp(Graph<V> g, Node<V> source) {
		HashMap<Node<V>, HeapEntry<Node<V>>> map = new HashMap<>();
		String res = "Distanze dal nodo "+ source + " [";
		for (Node<V> v : g.getNodes()) {
			v.timestamp = 100000;
		}
		source.timestamp = 0;
		MinHeap<Node<V>> queue = new MinHeap<>();
		for (Node<V> v : g.getNodes()) {
			map.put(v, queue.insert(v.timestamp, v));
		}
		while (!queue.isEmpty()) {
			HeapEntry<Node<V>> e1 = queue.removeMin();
			Node<V> v = e1.getValue();
			for (Edge<V> edge : g.graph.get(v)) {
				Node<V> u = edge.getTarget();
				int length = edge.getSource().timestamp + edge.getWeight();
				if (length < u.timestamp) {
					u.timestamp = length;
					queue.replaceKey(map.get(u), length);
				}
			}
		}
		for (Node<V> u : g.getNodes()) {
			res += u.getElement() + ":" + u.timestamp + ", ";
		}
		res = res.substring(0, res.length()-2);
		return res + "]";
	}

	public static <V> void apsp(Graph<V> g) {
		for (Node<V> v : g.getNodes()) {
			System.out.println(sssp(g, v));
		}
	}
}
