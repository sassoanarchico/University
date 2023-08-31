import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.io.File;

public class Graph<V> {

    private LinkedList<GraphNode<V>> nodes;
    private int n_nodes, n_edges;

    public Graph () {
      nodes = new LinkedList<GraphNode<V>>();
    }

    public List<GraphNode<V>> getNodes() {
        LinkedList<GraphNode<V>> r = new LinkedList<>();
        for (GraphNode<V> n :nodes) {
          try {
            r.add((GraphNode<V>) n.clone());
          } catch (CloneNotSupportedException e) {
            e.printStackTrace();
          }
        }
        return r;
    }

    public List<GraphNode<V>> getNeighbors(GraphNode<V> n){
        LinkedList<GraphNode<V>> r = new LinkedList<>();
        for (GraphNode<V> node: n.outEdges) {
          try {
            r.add((GraphNode<V>) node.clone());
          } catch (CloneNotSupportedException e) {
            e.printStackTrace();
          }
        }
        return r;
    }

    public GraphNode<V> addNode(V value) {
      GraphNode<V> r = new GraphNode<>();
      r.value = value;
      r.outEdges = new LinkedList<GraphNode<V>>();
      r.state = GraphNode.Status.UNEXPLORED;
      
      for (GraphNode<V> n: nodes) {
        if (n.value == value) {
          return r;
        }
      }
      nodes.add(r);
      n_nodes++;
      return r;
    }

    public void addEdge(GraphNode<V> s, GraphNode<V> t) {
        s.outEdges.add(t);
        t.outEdges.add(s);
        n_edges++;
    }

    public V getNodeValue(GraphNode<V> n) {
        return n.value;
    }

    public void removeEdge(GraphNode<V> v1, GraphNode<V> v2){
      removeEdgeAux(v1, v2);
      removeEdgeAux(v2, v1);
    }
    private void removeEdgeAux(GraphNode<V> v1, GraphNode<V> v2){
      Iterator<GraphNode<V>> it = nodes.iterator();
      while (it.hasNext()) {
        GraphNode<V> n1 = it.next();
        Iterator<GraphNode<V>> it2 = n1.outEdges.iterator();
        if (n1.equals(v1)) {
          while (it2.hasNext()) {
            GraphNode<V> n2 = it2.next();

            if (n2.equals(v2)) {
              it2.remove();
            }
          }
        }
      }
    }

    public void removeNode(GraphNode<V> v){

    }

    public static <V> Graph<V> readFF(File input){
      return null;
    }

    public String printAdj() {
		return "";
    }

    @Override
    public String toString(){
      return null;
    }

    public int nConComp(){
      return 0;
    }

    public List<Graph<V>> getConComp(){
      return null;
    }

	public static class GraphNode<V> implements Cloneable{

        public enum Status {UNEXPLORED, EXPLORED, EXPLORING}

        protected V value;
        protected LinkedList<GraphNode<V>> outEdges;

        // keep track status
        protected Status state;

		@Override
		public String toString() {
			return "GraphNode [value=" + value + ", state=" + state + "]";
		}

		@Override
		protected Object clone() throws CloneNotSupportedException {
			return super.clone();
		}
		
		
    }

}
