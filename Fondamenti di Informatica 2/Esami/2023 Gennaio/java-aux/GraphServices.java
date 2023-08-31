import java.util.*;

public class GraphServices {


	public static <V> int max_dist(Graph<V> g, Graph.GraphNode<V> source) {
		g.resetStatus();
		int max_ret = 0;
		Queue<Graph.GraphNode<V>> q = new LinkedList<>();
		q.add(source);
		while (!q.isEmpty()) {
			Graph.GraphNode<V> v = q.poll();
			v.state = Graph.GraphNode.Status.EXPLORING;
			for (Graph.GraphNode<V> ed: v.outEdges) {
				if (ed.state == Graph.GraphNode.Status.UNEXPLORED) {
					ed.state =Graph.GraphNode.Status.EXPLORING;
					ed.timestamp = v.timestamp + 1;
					q.add(ed);
					if (ed.timestamp > max_ret) max_ret = ed.timestamp;
				}
			}
		}	
		return max_ret;
	}


}
