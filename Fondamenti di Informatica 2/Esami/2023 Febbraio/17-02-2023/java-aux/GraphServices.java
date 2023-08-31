import java.util.*;

public class GraphServices {


	public static <V> void kdist(Graph<V> g, Graph.GraphNode<V> source, int k) {
		g.resetStatus();
		String res = source.value + " ";
		Queue<Graph.GraphNode<V>> queue = new LinkedList<>();
		source.timestamp = 0;
		queue.add(source);
		while (!queue.isEmpty()) {
			Graph.GraphNode<V> v = queue.poll();
			v.state = Graph.GraphNode.Status.EXPLORED;
			for (Graph.GraphNode<V> u : v.outEdges) {
				if (u.state == Graph.GraphNode.Status.UNEXPLORED) {
					u.state = Graph.GraphNode.Status.EXPLORED;
					queue.add(u);
					u.timestamp = v.timestamp + 1;
					if (u.timestamp <= k) res += u.value + " ";
				}
			}
		}
		System.out.println(res);
	}

}
