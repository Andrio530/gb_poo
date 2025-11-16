#include "ProcessQueue.h"
#include "Process.h"
#include "ProcessQueue.h"
ProcessQueue::ProcessQueue() : head(nullptr), tail(nullptr), count(0) {}
ProcessQueue::~ProcessQueue() { clear(); }
void ProcessQueue::push_back(Process *p)
{
  Node *n = new Node(p);
  if (!head)
    head = tail = n;
  else
  {
    tail->next = n;
    tail = n;
  }
  count++;
}
Process *ProcessQueue::pop_front()
{
  if (!head)
    return nullptr;
  Node *n = head;
  Process *p = n->proc;
  head = head->next;
  if (!head)
    tail = nullptr;
  n->proc = nullptr;
  delete n;
  count--;
  return p;
}
Process *ProcessQueue::find_by_pid(int pid) const
{
  Node *c = head;
  while (c)
  {
    if (c->proc->getPid() == pid)
      return c->proc;
    c = c->next;
  }
  return nullptr;
}
Process *ProcessQueue::remove_by_pid(int pid)
{
  Node *p = nullptr, *c = head;
  while (c)
  {
    if (c->proc->getPid() == pid)
    {
      if (p)
        p->next = c->next;
      else
        head = c->next;
      if (c == tail)
        tail = p;
      Process *proc = c->proc;
      c->proc = nullptr;
      delete c;
      count--;
      return proc;
    }
    p = c;
    c = c->next;
  }
  return nullptr;
}
bool ProcessQueue::empty() const { return !head; }
int ProcessQueue::size() const { return count; }
void ProcessQueue::printAll() const
{
  cout << "--- Fila (" << count << ") ---\n";
  Node *c = head;
  while (c)
  {
    c->proc->printInfo();
    c = c->next;
  }
  cout << "-----------------------\n";
}
void ProcessQueue::clear()
{
  Node *c = head;
  while (c)
  {
    Node *n = c->next;
    delete c;
    c = n;
  }
  head = tail = nullptr;
  count = 0;
}
bool ProcessQueue::saveToFile(const string &fn) const
{
  ofstream ofs(fn);
  if (!ofs)
    return false;
  Node *c = head;
  while (c)
  {
    ofs << c->proc->serialize() << "\n";
    c = c->next;
  }
  return true;
}
bool ProcessQueue::loadFromFile(const string &fn)
{
  ifstream ifs(fn);
  if (!ifs)
    return false;
  string line;
  while (getline(ifs, line))
  {
    if (line.empty())
      continue;
    vector<string> p;
    stringstream ss(line);
    string tmp;
    while (getline(ss, tmp, '|'))
      p.push_back(tmp);
    if (p.empty())
      continue;
    string type = p[0];
    int pid = (p.size() >= 2) ? stoi(p[1]) : -1;
    if (type == "COMPUTE")
    {
      string e = (p.size() >= 3) ? p[2] : "";
      push_back(new ComputingProcess(e, pid));
    }
    else if (type == "WRITE")
    {
      string e = (p.size() >= 3) ? p[2] : "";
      push_back(new WritingProcess(e, pid));
    }
    else if (type == "READ")
    {
      push_back(new ReadingProcess(this, pid));
    }
    else if (type == "PRINT")
    {
      push_back(new PrintingProcess(this, pid));
    }
  }
  return true;
}
