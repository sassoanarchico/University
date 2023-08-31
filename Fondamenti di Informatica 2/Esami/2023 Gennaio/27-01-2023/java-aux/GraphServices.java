import java.util.*;

public class GraphServices {


	public static <V> int max_dist(Graph<V> g, Graph.GraphNode<V> source) {
		g.resetStatus();
		int max_dist = 0;
		Queue<Graph.GraphNode<V>> queue = new LinkedList<>();
		source.timestamp = 0;
		queue.add(source);
		while (!queue.isEmpty()) {
			Graph.GraphNode<V> v = queue.poll();
			v.state = Graph.GraphNode.Status.EXPLORED;
			for (Graph.GraphNode<V> u : g.getOutNeighbors(v)) {
				if (u.state == Graph.GraphNode.Status.UNEXPLORED) {
					u.state = Graph.GraphNode.Status.EXPLORING;
					u.timestamp = v.timestamp + 1;
					queue.add(u);
					if (u.timestamp > max_dist) max_dist = u.timestamp;
				}
			}
		}
		return max_dist;
	}
}
