import java.util.*;

public class GraphServices {

	
	public static <V> void bfs(Graph<V> g) {
		
		for (Node<V> v: g.getNodes()) {
			resetStatus(g);
			bfs(g, v);
		}
	}

	public static <V> void sssp(Graph<V> g, Node<V> source) {
		MinHeap<Node<V>> pq = new MinHeap<>();
		Map<Node<V>, HeapEntry<Node<V>>> pqTokens = new HashMap<>();

		StringBuilder sb = new StringBuilder();
		sb.append("Shortest path a partire dal nodo " + source.getElement() + "\n");

		for (Node<V> v: g.getNodes()) {
			if (v == source) v.map = 0;
			else v.map = 100000;
			pqTokens.put(v, pq.insert(v.map, v));
		}

		while(!pq.isEmpty()) {
			HeapEntry<Node<V>> e1 = pq.removeMin();
			Node<V> v = e1.getValue();
			//sb.append("Nodo: " + v.getElement() +", Distanza: " + v.map +"\n");
			for (Edge<V> e: g.getOutEdges(v)) {
				Node<V> u = e.getTarget();
				int wg = e.getWeight();
				if (v.map + wg < u.map) {
					u.map = wg + v.map;
					pq.insert(u.map, u);
				}
			}
		}

		for (Node<V> n: g.getNodes()) {
			sb.append("Nodo: " + n.getElement() +", Distanza: " + n.map +"\n");
		}

		System.out.println(sb);
	}
	
	public static <V> void mst(Graph<V> g) {
		resetStatus(g);
        MinHeap<Edge<V>> heap = new MinHeap<>();
        for (Edge<V> e : g.getEdges()){
            heap.insert(e.getWeight(), e);
        }
        LinkedList<Node<V>> nodes = new LinkedList<>();
        int i = 0;
		Map<Node<V>, Integer> positions = new HashMap<>();
        for (Node<V> n: g.getNodes()){
            n.map = i++;
            nodes.addLast(n);
			positions.put(n, n.map);
        }
		
        Partition<V> part = new Partition<>(nodes);
        while(heap.size() > g.getNodes().size() && !heap.isEmpty()){
            Edge<V> e = heap.removeMin().getValue();
            Node<V> u = e.getSource();
            Node<V> v = e.getTarget();
			List<Node<V>> a = part.find(positions.get(u));
			List<Node<V>> b = part.find(positions.get(v));
			if (a != b) {
				System.out.println(u + " -> "+ v);
				part.union(u.map, v.map);
			}
        }
	}
	 



//AUXILIAR FUNCTIONS
	private static <V> void resetStatus(Graph<V> g) {
		for (Node<V> v: g.getNodes()) {
			v.stato = Node.Stato.UNEXPLORED;
		}
	}

	private static <V> void bfs(Graph<V> g, Node<V> source) {
		source.map = 0;
		source.stato = Node.Stato.EXPLORED;
		Queue<Node<V>> q = new LinkedList<>();
		q.add(source);

		StringBuilder sb = new StringBuilder();
		sb.append("BFS dal nodo: " + source.getElement() +"\n");
		while(!q.isEmpty()) {
			Node<V> v = q.remove();
			sb.append("Elemento: " + v.getElement() + ", Livello: " + v.map + "\n");
			for (Edge<V> e: g.getOutEdges(v)) {
				Node<V> u = e.getTarget();
				if (u.stato == Node.Stato.UNEXPLORED) {
					u.map = v.map + 1;
					u.stato = Node.Stato.EXPLORING;
					q.add(u);
				}
			}
		}

		
		System.out.println(sb);
	}
}




