import java.util.*;

public abstract class Node {
	protected Node parent;
	protected ArrayList<String> Keys;
	protected int Degree;
	
	public int getKeysize() {
		return this.Keys.size();
	}
	//삽입
	abstract void insert(BPTree bplus ,String data);
	abstract void PreOrder();
	abstract Node getRoot(Node node);
	//abstract Node delete(String data);
	
}

class LeafNode extends Node{
	private LeafNode next;
	//private Map<String, ArrayList<String>> data;
	
	LeafNode(int Degree){
		this.parent = null;
		this.next = null;
		Keys = new ArrayList<String>(Degree-1);
		//data = new HashMap<String, ArrayList<String>>();
		
		this.Degree  = Degree;
	}
	
	//리프노드에서의 삽입
	@Override
	public void insert(BPTree bplus, String data) {
		//처음온 데이터는 Keys에 추가
		if(this.Keys.indexOf(data) < 0)
		{
			this.Keys.add(data);
			Collections.sort(this.Keys);
		}
		//중복데이터는 키에 넣지않음
		
		//이하 과제 나오면 data처리
		
		//넣은 후 분할이 일어나는 케이스 
		//case: split in leafnode
		if( this.getKeysize() == this.Degree) {
			//우선 반 쪼개기 위해 새 리프노드 생성 후 키를 반으로 가짐
			LeafNode newLeaf = new LeafNode(this.Degree);
			newLeaf.Keys.addAll(this.Keys);
			for(int i = 0; i < 3; i++) {
				this.Keys.remove(0);	//큰 값남기기
				newLeaf.Keys.remove(3);	//작은 값 남기기
			}
			//스플릿 후 case1: parent가 없을때
			// 새로 노드 생성후 연결
			if(this.parent == null)
			{
				InternalNode newparent = new InternalNode(Degree);
				newparent.Keys.add(this.Keys.get(0));	//부모 노드에 들어갈 값은 우측 노드의 가장작은 값
				//작은 값을 가진 노드부터 차례로 삽입
				newparent.childs.add(newLeaf);
				newparent.childs.add(this);	
				this.parent = newLeaf.parent = newparent;	//부모노드 설정
				bplus.setRoot(getRoot(this)); //루트지정
			}
			//스플릿 후 case2: parent가 있을때
		}
	}
	
	@Override
	void PreOrder() {
		for(int i = 0; i < this.Keys.size(); i++) {
			System.out.print(this.Keys.get(i)+" ");
		}
	}

	@Override
	Node getRoot(Node node) {
		if(this.parent == null)
			return this;
		
		return this.parent.getRoot(node);
	}

}
//인터널 노드에서의 삽입 pointer 역할
class InternalNode extends Node{
	protected ArrayList<Node> childs; //노드 포인터
	
	InternalNode(int Degree){
		this.parent = null;
		Keys = new ArrayList<String>(Degree-1);
		childs = new ArrayList<Node>(Degree);
		this.Degree = Degree;
	}
	@Override
	void insert(BPTree bplus, String data) {
		int index = 0;
		//index를 이용해서 child에 접근
		for(index = 0; index < this.Degree-1;) {
		//들어온 데이터가 노드 안의 해당 인덱스위치의 데이터보다 크면 인덱스 증가
			if(data.compareTo(this.Keys.get(index)) < 0)
				index++;
			//같다면 리턴
			else if(data.compareTo(this.Keys.get(index)) == 0)
				return;
			//맞는위치라면 
			else
				break;
		}
		this.childs.get(index).insert(bplus, data);	
	}
	@Override
	void PreOrder() {
		for(int i = 0; i < this.Keys.size(); i++) {
			System.out.print(this.Keys.get(i)+" ");
		}
		System.out.println();
		for(int i = 0; i < this.childs.size(); i++) {
			this.childs.get(i).PreOrder();
		}
	}
	@Override
	Node getRoot(Node node) {
		if(this.parent == null)
			return this;
		return this.parent.getRoot(node);
	}
}