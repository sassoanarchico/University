import java.util.*;

public class GraphServices {


	public static <V> void bfs(Graph<V> g, Graph.GraphNode<V> source) {
		Queue<Graph.GraphNode<V>> q = new LinkedList<>();
		source.state = Graph.GraphNode.Status.EXPLORED;
		source.timestamp = 0;
		q.add(source);
		StringBuilder sb = new StringBuilder();
		sb.append("BFS da " + source.value + ":\n");
		while(!q.isEmpty()) {
			Graph.GraphNode<V> v = q.remove();
			sb.append("Livello " +v.value + ": " + v.timestamp +"\n");
			for(Graph.GraphNode<V> u: g.getOutNeighbors(v)) {
				if (u.state == Graph.GraphNode.Status.UNEXPLORED) {
					u.timestamp = v.timestamp+1;
					u.state = Graph.GraphNode.Status.EXPLORED;
					q.add(u);
				}
				
			}
		}
		System.out.println(sb);
	
	}
}
