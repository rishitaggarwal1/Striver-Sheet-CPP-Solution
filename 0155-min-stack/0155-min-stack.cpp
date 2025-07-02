class MinStack {
public:
    stack<pair<int,int> > s;
    int m=INT_MAX;
    MinStack() {
        
    }
    
    void push(int val) {
        if(s.empty()) m=INT_MAX;
        if(val<m)
            m=val;
        s.push({val,m});
    }
    
    void pop() {
        if(s.empty())   return;
        s.pop();
        if(!s.empty())
            m=s.top().second;
    }
    
    int top() {
        return s.top().first;
    }
    
    int getMin() {
        return s.top().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */