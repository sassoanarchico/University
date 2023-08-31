import java.util.LinkedList;

public class GraphNode<V> implements Cloneable{
	public static enum Status {UNEXPLORED, EXPLORED, EXPLORING}

	protected V value;
	protected LinkedList<GraphNode<V>> outEdges;

	// keep track status
	protected Status state;
	protected int timestamp;

	@Override
	public String toString() {
		return "GraphNode [value=" + value + ", state=" + state + "]";
	}

	@Override
	protected Object clone() throws CloneNotSupportedException {
		return (GraphNode<V>) this;
	}
}
