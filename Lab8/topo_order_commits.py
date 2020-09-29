#!/usr/bin/env python3
import zlib
import os
import sys


class CommitNode:
    def __init__(self, commit_hash):
        """
        :type commit_hash: str
        """
        self.commit_hash = commit_hash
        self.parents = set()
        self.children = set()
        self.status = 0


def topo_order_commits():
    # step1
    cwd = os.getcwd()
    discover = False
    while not discover:
        all_dirs = os.listdir(cwd)
        for i in all_dirs:
            if i == ".git":
                discover = True
                break
        if not discover:
            if cwd == "/":
                sys.stderr.write("Not inside a Git repository\n")
                exit(1)
            cwd = os.path.dirname(cwd)

    # step2
    branches = dict()
    commit_nodes = dict()
    root_commits = set()
    hash_set = set()
    branch_dir = os.path.join(cwd, ".git/refs/heads")
    # for f in os.listdir(branch_dir):
    #     file = os.path.join(branch_dir, f)
    os.chdir(branch_dir)
    for root, dirs, files in os.walk("."):
        for name in files:
            file_path = os.path.join(root, name)
            if os.path.isfile(file_path):
                branch_name = file_path[2:]
                checksum_hash = open(file_path).readline()[:40]
                if checksum_hash not in branches:
                    branches[checksum_hash] = []
                branches[checksum_hash].append(branch_name)
                hash_set.add(checksum_hash)

    # step3
    hash_list = sorted(hash_set)
    while len(hash_list) > 0:
        a = hash_list[-1]
        hash_list.pop()
        if a not in commit_nodes:
            commit_nodes[a] = CommitNode(a)
            subdirectory = a[:2]
            filename = a[2:]
            obj_dir = os.path.join(cwd, ".git/objects", subdirectory, filename)
            compressed_contents = open(obj_dir, 'rb').read()
            decompressed_contents = zlib.decompress(compressed_contents).decode().splitlines()
            for p in decompressed_contents:
                if p.startswith("parent"):
                    parent_hash = p[7:]
                    commit_nodes[a].parents.add(parent_hash)
                    if parent_hash not in commit_nodes:
                        hash_list.append(parent_hash)
            if len(commit_nodes[a].parents) == 0:
                root_commits.add(a)

    for node in commit_nodes:
        for parent in list(commit_nodes[node].parents):
            commit_nodes[parent].children.add(node)

    # step4
    queue_sort = []
    visit = set()
    for s in sorted(list(root_commits)):
        stack = [s]
        while stack:
            v = stack[-1]
            visit.add(v)
            flag = 0
            for child in sorted(list(commit_nodes[v].children)):
                if child not in visit:
                    stack.append(child)
                    flag = 1
            if flag == 0:
                if v not in queue_sort:
                    queue_sort.append(v)
                stack.pop()

    # print(queue_sort)
    # def dfs_visit(commits, v, visited, queue):
    #     visited.add(v)
    #     for child in list(commits[v].children):
    #         if child not in visited:
    #             dfs_visit(commits, child, visited, queue)
    #     queue.append(v)
    #
    # for node in sorted(root_commits):
    #     if node not in visit:
    #         dfs_visit(commit_nodes, node, visit, queue_sort)

    # step5
    for c in queue_sort:
        print(c, end="")
        if c in branches:
            for branch_name in sorted(branches[c]):
                print(" " + branch_name, end="")
        print("")
        if queue_sort.index(c) != len(queue_sort) - 1:
            next = queue_sort[queue_sort.index(c) + 1]
        else:
            break
        if next not in commit_nodes[c].parents:
            if len(commit_nodes[c].parents) > 0:
                for par in list(commit_nodes[c].parents)[:-1]:
                    print(par, end=" ")
                print(list(commit_nodes[c].parents)[-1], end="")
            print("=")
            print("")
            print("=", end="")
            if len(commit_nodes[next].children) > 0:
                for child in list(commit_nodes[next].children)[:-1]:
                    print(child, end=" ")
                print(list(commit_nodes[next].children)[-1], end="")
            print("")


if __name__ == '__main__':
    topo_order_commits()
