#include "ProcessQueue.h"
#include "Process.h"
#include "ComputingProcess.h"
#include "WritingProcess.h"
#include "ReadingProcess.h"
#include "PrintingProcess.h"
ProcessQueue::ProcessQueue() : head(nullptr), tail(nullptr), count(0) {}
ProcessQueue::~ProcessQueue() { clear(); }
void ProcessQueue::push_back(Process *p)
{
  Nodo<Process *> *n = new Nodo<Process *>(p);
  if (!head)
    head = tail = n;
  else
  {
    tail->setProximo(n);
    tail = n;
  }
  count++;
}
Process *ProcessQueue::pop_front()
{
  if (!head)
    return nullptr;
  Nodo<Process *> *n = head;
  Process *p = n->getDado();
  head = head->getProximo();
  if (!head)
    tail = nullptr;
  delete n;
  count--;
  return p;
}
Process *ProcessQueue::find_by_pid(int pid) const
{
  Nodo<Process *> *c = head;
  while (c)
  {
    if (c->getDado()->getPid() == pid)
      return c->getDado();
    c = c->getProximo();
  }
  return nullptr;
}
Process *ProcessQueue::remove_by_pid(int pid)
{
  Nodo<Process *> *p = nullptr, *c = head;
  while (c)
  {
    if (c->getDado()->getPid() == pid)
    {
      if (p)
        p->setProximo(c->getProximo());
      else
        head = c->getProximo();
      if (c == tail)
        tail = p;
      Process *proc = c->getDado();
      delete c;
      count--;
      return proc;
    }
    p = c;
    c = c->getProximo();
  }
  return nullptr;
}
bool ProcessQueue::empty() const { return !head; }
int ProcessQueue::size() const { return count; }
void ProcessQueue::printAll() const
{
  cout << "--- Fila (" << count << ") ---\n";
  Nodo<Process *> *c = head;
  while (c)
  {
    c->getDado()->printInfo();
    c = c->getProximo();
  }
  cout << "-----------------------\n";
}
void ProcessQueue::clear()
{
  Nodo<Process *> *c = head;
  while (c)
  {
    Nodo<Process *> *n = c->getProximo();
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
  Nodo<Process *> *c = head;
  while (c)
  {
    ofs << c->getDado()->serialize() << "\n";
    c = c->getProximo();
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
