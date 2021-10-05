import java.util.*;

public class Node {
	protected Node parent;
	protected ArrayList<String> Keys;
	
	public int getKeysize() {
		return this.Keys.size();
	}

	public Node insert(String data, int max_Key) {
		return null;
	}

}

class LeafNode extends Node{
	private LeafNode next;
	private ArrayList<sets> data;
	
	LeafNode(int Degree){
		this.parent = null;
		this.next = null;
		Keys = new ArrayList<String>(Degree-1);
		data = new ArrayList<sets>(Degree-1);
	}
	
	//리프노드에서의 삽입
	public Node insert(String data, int max_Key) {
		this.Keys.add(data);
		Collections.sort(this.Keys);
		this.data.get(this.Keys.indexOf(data)).insert(data);
		
		return this;
	}
	
	class sets{
		private HashSet<String> dataset;
		
		sets(){
			dataset = new HashSet<String>();
		}
		
		void insert(String data) {
			this.dataset.add(data);
		}
	}
}
//인터널 노드에서의 삽입 pointer 역할
class InternalNode extends Node{
	private ArrayList<Node> childs;
	
	InternalNode(int Degree){
		this.parent = null;
		Keys = new ArrayList<String>(Degree-1);
		childs = new ArrayList<Node>(Degree);
	}
	
	public Node insert(String data, int max_Key) {
		int index;
		for(index = 0; index < max_Key;) {
			if(data.compareTo(this.Keys.get(index)) < 0)
				index++;
			else if(data.compareTo(this.Keys.get(index)) == 0)
				return null;
			else
				break;
		}
		return childs.get(index).insert(data, max_Key);
	}
}