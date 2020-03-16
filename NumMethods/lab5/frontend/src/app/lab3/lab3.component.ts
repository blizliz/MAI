import {Component, OnInit} from '@angular/core';

declare var Plotly: any;
declare var iterativeMethod: any;
declare var SeidelMethodSolution: any;

function phi0(y) {
  return 0;
}

function phi1(y) {
  return 1 - y * y;
}

function phi2(x) {
  return 0;
}

function phi3(x) {
  return x * x - 1;
}

function analSolutionFun(x, y) {
  return x * x - y * y;
}

function analSolutionGrid(N, l) {
  const h = l / N;
  const grid = [];
  for (let x = 0; x < N; x++) {
    grid[x] = [];
    for (let y = 0; y < N; y++) {
      grid[x][y] = analSolutionFun(x * h, y * h);
    }
  }
  return grid;
}

function fillMatrix(dim, value) {
  const matrix = []
  for (let i = 0; i < dim; i++) {
    matrix[i] = Array(dim).fill(value);
  }
  return matrix;
}

function vectorToMatrix(vec, size) {
  const matrix = fillMatrix(size, 0);
  for (let i = 0; i < size; i++) {
    matrix[i] = vec.slice(i * size, size * (i + 1));
  }
  return matrix;
}

function getEquationsSystem(N, l) {
  const h = l / N;
  const innerGridSize = N - 1;
  const size = innerGridSize * innerGridSize;
  const A = fillMatrix(size, 0);
  const b = Array(size).fill(0);
  for (let i = 0; i < innerGridSize; i++) {
    for (let j = 0; j < innerGridSize; j++) {
      A[i * innerGridSize + j][i * innerGridSize + j] += -4;

      if (i + 1 === innerGridSize) {
        b[i * innerGridSize + j] -= phi1(j * h);
      } else {
        A[i * innerGridSize + j][(i + 1) * innerGridSize + j] += 1;
      }

      if (i - 1 === -1) {
        A[i * innerGridSize + j][i * innerGridSize + j] += 1;
      } else {
        A[i * innerGridSize + j][(i - 1) * innerGridSize + j] += 1;
      }

      if (j + 1 === innerGridSize) {
        b[i * innerGridSize + j] -= phi3(i * h);
      } else {
        A[i * innerGridSize + j][i * innerGridSize + (j + 1)] += 1;
      }

      if (j - 1 === -1) {
        A[i * innerGridSize + j][i * innerGridSize + j] += 1;
      } else {
        A[i * innerGridSize + j][i * innerGridSize + (j - 1)] += 1;
      }
    }
  }
  return {A, b};
}

function LibmanMethod(N, l, eps) {
  const systemEq = getEquationsSystem(N, l);
  const u = iterativeMethod(systemEq.A, systemEq.b, eps);
  const innerGridSize = N - 1;
  const grid = vectorToMatrix(u, innerGridSize);
  return grid;
}

function SeidelMethod(N, l, eps) {
  const systemEq = getEquationsSystem(N, l);
  const u = SeidelMethodSolution(systemEq.A, systemEq.b, eps);
  const innerGridSize = N - 1;
  const grid = vectorToMatrix(u, innerGridSize);
  return grid;
}

@Component({
  selector: 'app-lab3',
  templateUrl: './lab3.component.html',
  styleUrls: ['./lab3.component.css']
})
export class Lab3Component implements OnInit {

  constructor() {
  }

  ngOnInit() {
  }

  solve(N, l, eps) {
    N = +N;
    l = +l;
    eps = +eps;

    const gridAnal = analSolutionGrid(N, l);
    const gridLibman = LibmanMethod(N, l, eps);
    const gridSeidel = SeidelMethod(N, l, eps);

    const dataAnalytic = [{
      z: gridAnal,
      type: 'surface'
    }];
    const layoutAnalytic = {
      title: 'Analytic',
      autosize: false,
      width: 400,
      height: 400,
      margin: {
        l: 65,
        r: 50,
        b: 65,
        t: 90,
      }
    };
    Plotly.newPlot('analytic', dataAnalytic, layoutAnalytic);

    const layoutLibman = {
      title: 'Libman method',
      autosize: false,
      width: 400,
      height: 400,
      margin: {
        l: 65,
        r: 50,
        b: 65,
        t: 90,
      }
    };
    const dataLibman = [{
      z: gridLibman,
      type: 'surface'
    }];
    Plotly.newPlot('libman', dataLibman, layoutLibman);

    const layoutSeidel = {
      title: 'Seidel method',
      autosize: false,
      width: 400,
      height: 400,
      margin: {
        l: 65,
        r: 50,
        b: 65,
        t: 90,
      }
    };
    const dataSeidel = [{
      z: gridLibman,
      type: 'surface'
    }];
    Plotly.newPlot('seiden', dataSeidel, layoutSeidel);
  }
}
