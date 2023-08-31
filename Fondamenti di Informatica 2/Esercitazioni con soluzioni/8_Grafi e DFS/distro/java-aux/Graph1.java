import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;

import org.w3c.dom.Node;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Graph1<V> {

  private LinkedList<GraphNode<V>> nodes;
  private int n_nodes, n_edges;

    public Graph1 () {
      nodes = new LinkedList<GraphNode<V>>();
    }

    public List<GraphNode<V>> getNodes(){
        List<GraphNode<V>> r = new LinkedList<>();
        for (GraphNode<V> n : nodes) {
          try{
            r.add((GraphNode<V>) n.clone());
          } catch (CloneNotSupportedException e) {
            e.printStackTrace();
          }
        }
        return (List<GraphNode<V>>) r;
    }

    public List<GraphNode<V>> getNeighbors(GraphNode<V> n){
        List<GraphNode<V>> r = new LinkedList<>();
        for (GraphNode<V> edge: n.outEdges) {
          try{
            r.add((GraphNode<V>) edge.clone());
          } catch(CloneNotSupportedException e) {
            e.printStackTrace();
          }
        }
        return (List<GraphNode<V>>) r;
    }

    public GraphNode<V> addNode(V value) {
        GraphNode<V> node = new GraphNode<V>(); 
        node.value = value;
        node.outEdges = new LinkedList<GraphNode<V>>();
        nodes.add(node);
        n_nodes++;
        return node;
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
      v1.outEdges.remove(v2);
      v2.outEdges.remove(v1);
      n_edges--;
    }

    public void removeNode(GraphNode<V> v){
      nodes.remove(v);
    }

    public static <V> Graph1<V> readFF(File input){
      Graph1<V> ret = new Graph1<>();

      try {
        BufferedReader br = new BufferedReader(new FileReader(input));
        String fLine = br.readLine();
        StringTokenizer tok = new StringTokenizer(fLine);
        int v = Integer.parseInt(tok.nextToken());
        int e = Integer.parseInt(tok.nextToken());

        for (int i =0 ; i < e; i++) {
          tok = new StringTokenizer(br.readLine());

          while(tok.hasMoreTokens()) {
            GraphNode<V> v1 = ret.addNode((V)tok.nextToken());
            GraphNode<V> v2 = ret.addNode((V)tok.nextToken());
            ret.addEdge(v1, v2);
          }
        }
        br.close();

        if (ret.n_nodes<v) {
          int rem = v - ret.n_nodes;
          int name = e+1;

          for (int i =0 ; i < rem; i++) { 
            ret.addNode((V) (name + ""));
            name++;
          }
        }
      } catch (FileNotFoundException e) {
        e.printStackTrace();
      } catch(IOException e) {
        e.printStackTrace();
      }

      return ret;
    }

    public String printAdj() {
		  StringBuffer toRet = new StringBuffer();
        
        for(GraphNode<V> v : this.nodes) {
            toRet.append(v.value + ": ");

            for(GraphNode<V> e: v.outEdges)
                toRet.append(e.value + " ");
            
            toRet.append("\n");
        }
        
        return toRet.toString();
    }

    @Override
    public String toString(){
      return null;
    }

    private void DFS(GraphNode<V> node) {
      if (node.state != GraphNode.Status.UNEXPLORED) {
        return;
      }
      node.state = GraphNode.Status.EXPLORING;
      for (GraphNode<V> n: node.outEdges) {
        if (n.state == GraphNode.Status.UNEXPLORED) {
          DFS(n);
        }
      }
      node.state = GraphNode.Status.EXPLORED;
    }
    
    public int nConComp(){
      int ret = 0;
      for (GraphNode<V> node: this.nodes) {
        if (node.state == GraphNode.Status.UNEXPLORED) {
          ret++;
          DFS(node);
        }
      }
      return ret;
    }

    public List<Graph1<V>> getConComp(){
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
