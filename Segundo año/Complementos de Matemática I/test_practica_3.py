#! /usr/bin/python
# -*- coding: utf-8 -*-

import unittest

from practica3 import (check_is_hamiltonian_trail,
                       check_is_hamiltonian_circuit,
                       check_is_eulerian_trail,
                       check_is_eulerian_circuit,
                       graph_has_eulerian_trail,
                       find_eulerian_circuit)


class TestIsHamiltoneanTrail(unittest.TestCase):
    graph_1 = ([], [])
    graph_2 = (['a'], [])
    graph_3 = (['a'], [('a', 'a')])
    graph_4 = (['a', 'b'], [('a', 'b')])
    graph_5 = (['a', 'b', 'c'], [('a', 'b'), ('b', 'c')])
    graph_6 = (['a', 'b', 'c', 'd'],
               [('a', 'b'), ('b', 'c'), ('a', 'd'), ('c', 'd'), ('d', 'a')])

    is_trail_cases = [
        (graph_1, []),
        (graph_4, [('a', 'b')]),
        (graph_5, [('a', 'b'), ('b', 'c')]),
        (graph_6, [('a', 'b'), ('b', 'c'), ('c', 'd')])
    ]

    is_not_trail_cases = [
        (graph_1, [('a', 'b')]),
        (graph_2, [('b', 'a')]),
        (graph_2, []),
        (graph_3, [('b', 'a')]),
        (graph_3, []),
        (graph_4, []),
        (graph_4, [('b', 'a')]),
        (graph_4, [('a', 'c'), ('c', 'b')]),
        (graph_5, [('b', 'c'), ('a', 'b')]),
        (graph_6, [('a', 'b'), ('b', 'c'), ('c', 'd'), ('d', 'a')])
    ]

    def test_is_trail_cases(self):
        for graph, path in self.is_trail_cases:
            result = check_is_hamiltonian_trail(graph, path)
            self.assertTrue(
                result,
                'caso: check_is_hamiltonian_trail({}, {})'.format(graph, path)
            )

    def test_is_not_trail_cases(self):
        for graph, path in self.is_not_trail_cases:
            result = check_is_hamiltonian_trail(graph, path)
            self.assertFalse(
                result,
                'caso: check_is_hamiltonian_trail({}, {})'.format(graph, path)
            )


class TestIsHamiltoneanCircuit(unittest.TestCase):
    graph_1 = ([], [])
    graph_2 = (['a'], [])
    graph_3 = (['a'], [('a', 'a')])
    graph_4 = (['a', 'b'], [('a', 'b'), ('b', 'a')])
    graph_5 = (['a', 'b', 'c'], [('a', 'b'), ('b', 'c')])
    graph_6 = (['a', 'b', 'c', 'd'],
               [('a', 'b'), ('b', 'c'), ('a', 'd'), ('c', 'd'), ('d', 'a')])
    graph_7 = (['a', 'b', 'c', 'd'],
              [('a', 'b'), ('b', 'c'), ('c', 'd'), ('d', 'b')])
    graph_8 = (['a', 'b', 'c', 'd'],
            [('a', 'b'), ('b', 'c'), ('c', 'a'), ('a', 'd')])

    is_circuit_cases = [
        (graph_1, []),
        (graph_3, [('a', 'a')]),
        (graph_4, [('a', 'b'), ('b', 'a')]),
        (graph_6, [('a', 'b'), ('b', 'c'), ('c', 'd'), ('d', 'a')])
    ]

    is_not_circuit_cases = [
        (graph_1, [('a', 'b')]),
        (graph_2, [('b', 'a')]),
        (graph_2, []),
        (graph_3, [('b', 'a')]),
        (graph_3, []),
        (graph_4, []),
        (graph_4, [('a', 'c'), ('c', 'a')]),
        (graph_5, [('b', 'c'), ('a', 'b')]),
        (graph_6, [('a', 'b'), ('b', 'c'), ('c', 'd')]),
        (graph_7, [('a', 'b'), ('b', 'c'), ('c', 'd'), ('d', 'b')]),
        (graph_8, [('a', 'b'), ('b', 'c'), ('c', 'a'), ('a', 'd')])
    ]

    def test_is_circuit_cases(self):
        for graph, path in self.is_circuit_cases:
            result = check_is_hamiltonian_circuit(graph, path)
            self.assertTrue(
                result,
                'caso: check_is_hamiltonian_circuit({}, {})'.format(graph, path)
            )

    def test_is_not_circuit_cases(self):
        for graph, path in self.is_not_circuit_cases:
            result = check_is_hamiltonian_circuit(graph, path)
            self.assertFalse(
                result,
                'caso: check_is_hamiltonian_circuit({}, {})'.format(graph, path)
            )


class TestIsEulerianTrail(unittest.TestCase):
    graph_1 = ([], [])
    graph_2 = (['a'], [])
    graph_3 = (['a'], [('a', 'a')])
    graph_4 = (['a', 'b'], [('a', 'b')])
    graph_5 = (['a', 'b', 'c'], [('a', 'b'), ('b', 'c')])
    graph_6 = (['a', 'b', 'c', 'd'],
               [('a', 'b'), ('b', 'c'), ('a', 'd'), ('c', 'd'), ('d', 'a')])

   is_trail_cases = [
       (graph_1, []),
       (graph_2, []),
       (graph_3,[('a', 'a')]),
       (graph_5, [('a', 'b'), ('b', 'c')]),
       (graph_6,[('a','d'),('d','a'),('a','b'),('b','c'),('c','d')])

   ]

   is_not_trail_cases = [
       (graph_1, [('a', 'b')]),
       (graph_2, [('b', 'a')]),
       (graph_3, [('b', 'a')]),
       (graph_3, []),
       (graph_4, []),
       (graph_4, [('b', 'a')]),
       (graph_4, [('a', 'c'), ('c', 'b')]),
       (graph_5, [('b', 'c'), ('a', 'b')]),
       (graph_6, [('a', 'b'), ('b', 'c'), ('c', 'd'), ('d', 'a')])
       (graph_6, [('a', 'b'), ('b', 'c'), ('c', 'd')])
   ]

class TestIsEulerianCircuit(unittest.TestCase):
    pass

class TestHasEulerianTrail(unittest.TestCase):
    pass


class TestFindEulerianCircuit(unittest.TestCase):
    pass

if __name__ == '__main__':
    unittest.main()
