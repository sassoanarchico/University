import java.util.*;

public class GraphServices {


	public static <V> void bfs(Graph<V> g, Graph.GraphNode<V> source) {
		//System.out.println("BFS da " + source.value + ":");
		Queue<Graph.GraphNode<V>> queue = new LinkedList<>();
		queue.add(source);
		source.timestamp = 0;
		while (!queue.isEmpty()) {
			Graph.GraphNode<V> v = queue.poll();
			System.out.println("Livello " + v.value + ": " + v.timestamp);
			for (Graph.GraphNode<V> u : v.outEdges) {
				if (u.state == Graph.GraphNode.Status.UNEXPLORED) {
					u.state = Graph.GraphNode.Status.EXPLORED;
					queue.add(u);
					u.timestamp = v.timestamp + 1;
				}
			}
		}
	}

}
