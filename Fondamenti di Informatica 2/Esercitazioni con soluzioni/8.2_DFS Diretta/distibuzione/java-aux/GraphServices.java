import java.util.LinkedList;
import java.util.List;
import java.util.Stack;


public class GraphServices<V> {

  /*                            SWEEP                           */ 

  public static <V> void sweep(Graph<V> g) {
    g.resetStatus();
    int time = 0;
    for (Graph.GraphNode<V> v: g.getNodes()) {
      sweep_aux(v, time++);
    }
  }

  private static <V> void sweep_aux(Graph.GraphNode<V> node, int time) {
    if (node.state != Graph.GraphNode.Status.UNEXPLORED)
      return;
    
    node.state = Graph.GraphNode.Status.EXPLORING;
    node.timestamp = time;
    for (Graph.GraphNode<V> cur: node.outEdges) {
      System.out.println("\t" + node.value + "(" + node.timestamp + ")->" + cur.value + "(" + cur.timestamp + 
      ")");
                  
      if (cur.state == Graph.GraphNode.Status.EXPLORED) {
          if (node.timestamp < cur.timestamp)
              System.out.println("FORWARD");
          else
              System.out.println("CROSS");
      }
      else if (cur.state == Graph.GraphNode.Status.EXPLORING) 
          System.out.println("BACK");
      else {
          System.out.println("TREE");
          sweep_aux(cur, time + 1);
      }
    }
    node.state = Graph.GraphNode.Status.EXPLORED;
    return;
    
  }




  /*                            TOPOLOGICAL SORT                           */ 
  
  public static <V> void topologicalSort(Graph<V> g) {
    if (isCyclic(g)) return;
    g.resetStatus();
    LinkedList<Graph.GraphNode<V>> l = new LinkedList<>();
    for (Graph.GraphNode<V> v: g.getNodes()) {
      if (v.state == Graph.GraphNode.Status.UNEXPLORED) {
        DFS(g, v, l);
      }
    }
    int n = g.getNodes().size();
    System.out.println("Topological sort:");
    while(!l.isEmpty()) {
      Graph.GraphNode<V> v = l.pop();
      v.timestamp = n--;
      System.out.println("Node: " + v.value + "(" + v.timestamp +")");
    }
  }

  private static <V> void DFS(Graph<V> g, Graph.GraphNode<V> v, LinkedList<Graph.GraphNode<V>> s) {
    if (v.state != Graph.GraphNode.Status.UNEXPLORED) return;
    
    v.state = Graph.GraphNode.Status.EXPLORING;
    
    for (Graph.GraphNode<V> u: v.outEdges) {
      
        DFS(g, u, s);
  
    }
    v.state = Graph.GraphNode.Status.EXPLORED;
    s.addFirst(v);
    return;
  }
  
  private static <V> boolean isCyclic(Graph<V> g) {
    g.resetStatus();
    for (Graph.GraphNode<V> v: g.getNodes()) {
      if (isCyclic(g, v)) return true;
    }
    return false;
  }

  private static <V> boolean isCyclic(Graph<V> g, Graph.GraphNode<V> v) {
    v.state = Graph.GraphNode.Status.EXPLORING;
    for (Graph.GraphNode<V> u: v.outEdges) {
      if (u.state == Graph.GraphNode.Status.EXPLORING) {
        System.out.println("Il grafo è ciclico");
        return true;
      } 
      else { 
        isCyclic(g, u);   
      }
    }
    v.state = Graph.GraphNode.Status.EXPLORED;
    return false;
  }



  /*                            STRONG CONNECTED COMPONENTS                           */ 

  public static <V> void strongConnectedComponents(Graph<V> g) {
    //g.resetStatus();
    LinkedList<Graph.GraphNode<V>> s = new LinkedList<>();
    for (Graph.GraphNode<V> v: g.getNodes()) {
      if (v.state == Graph.GraphNode.Status.UNEXPLORED) {
        DFS(g, v, s);
      }
    }
    g.resetStatus();
    
    for (Graph.GraphNode<V> v: s) {
      if (v.state == Graph.GraphNode.Status.UNEXPLORED) {
        LinkedList<Graph.GraphNode<V>> inv = new LinkedList<>();
        idfs(g, v, inv);
        System.out.println("\nStrong connected components:");
        for (Graph.GraphNode<V> u: inv) {
          System.out.print(u.value + " ");
        }
        System.out.println("");
      }
    }
  }

 

  private static <V> void idfs(Graph<V> g, Graph.GraphNode<V> v, LinkedList<Graph.GraphNode<V>> l) {
    if (v.state != Graph.GraphNode.Status.UNEXPLORED) return;
    
    v.state = Graph.GraphNode.Status.EXPLORING; 
    for (Graph.GraphNode<V> u: v.inEdges) {
      if (u.state == Graph.GraphNode.Status.UNEXPLORED) {
        idfs(g, u, l);
      }
    }
    l.addLast(v);
    v.state = Graph.GraphNode.Status.EXPLORED;
  }
  
}
