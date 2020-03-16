import { Component, OnInit } from '@angular/core';

declare var Plotly: any;
declare var tridiagonalMatrixAlgorithm: any;

function psi1SecondDeriv(x) {
  return -Math.sin(x) - Math.cos(x);
}

function psi1(x) {
  return Math.sin(x) + Math.cos(x);
}

function psi2(x, a) {
  return -a * (Math.sin(x) + Math.cos(x));
}

function phi0(t) {
  return 0;
}

function phil(t) {
  return 0;
}

function analSolutionFun(x, t, a) {
  return Math.sin(x - a * t) + Math.cos(x + a * t);
}

function analSolutionGrid(N, K, a, tau, h) {
  const grid = [];
  for (let k = 0; k < K; k++) {
    grid[k] = [];
    for (let j = 0; j < N; j++) {
      grid[k][j] = analSolutionFun(j * h, k * tau, a);
    }
  }
  return grid;
}

function explicitScheme(N, K, koeff, tau, h) {
  const sigma = (koeff * koeff * tau * tau) / (h * h);
  const grid = [];

  // fill the first layer (k = 0)
  grid[0] = [];
  for (let j = 0; j < N; j++) {
    const x = j * h;
    grid[0][j] = psi1(x);
  }

  // fill the second layer (k = 1)
  grid[1] = [];
  for (let j = 0; j < N; j++) {
    const x = j * h;
    // psi1 derivative is 0, then no third factor
    grid[1][j] = psi1(x) + psi2(x, koeff) * tau + koeff * koeff * psi1SecondDeriv(x) * tau * tau / 2;
  }

  // fill by common formula
  for (let k = 2; k < K; k++) {
    grid[k] = [];
    const t = k * tau;
    for (let j = 1; j < N - 1; j++) {
      grid[k][j] = sigma * grid[k - 1][j + 1]
        + (2 - 2 * sigma) * grid[k - 1][j]
        + sigma * grid[k - 1][j - 1]
        - grid[k - 2][j];
    }
    grid[k][0] =  grid[k][1] / (1 + h);
    grid[k][N - 1] = grid[k][N - 2] / (1 - h);
  }
  return grid;
}

function implicitScheme(N, K, koeff, tau, h) {
  const sigma = koeff * koeff * tau * tau / (h * h);
  const grid = [];

  // fill the first layer (k = 0)
  grid[0] = [];
  for (let j = 0; j < N; j++) {
    const x = j * h;
    grid[0][j] = psi1(x);
  }

  // fill the second layer (k = 1)
  grid[1] = [];
  for (let j = 0; j < N; j++) {
    const x = j * h;
    // psi1 derivative is 0, then no third factor
    grid[1][j] = psi1(x) + psi2(x, koeff) * tau + koeff * koeff * psi1SecondDeriv(x) * tau * tau / 2;
  }

  // fill by common formula
  for (let k = 2; k < K; k++) {
    grid[k] = [];
    const a = [];
    const b = [];
    const c = [];
    const d = [];

    a.push(0);
    b.push(-2 / h);
    c.push(1 / h);
    d.push(phi0(k * tau) * h / (-2));
    for (let j = 1; j < N - 1; j++) {
      a.push(sigma);
      b.push(-(1 + 2 * sigma));
      c.push(sigma);
      d.push(-2 * grid[k - 1][j] + grid[k - 2][j]);
    }
    a.push(-1 / h);
    b.push(1 / h);
    c.push(0);
    d.push(phil(k * tau) * h);

    grid[k] = tridiagonalMatrixAlgorithm(a, b, c, d);
  }
  return grid;
}

@Component({
  selector: 'app-lab2',
  templateUrl: './lab2.component.html',
  styleUrls: ['./lab2.component.css']
})

export class Lab2Component implements OnInit {
  l = Math.PI;
  h;
  tau;
  sigma;

  constructor() { }

  ngOnInit() {
  }

  solve(N, K, a, T) {
    a = +a;
    N = +N;
    K = +K;
    this.h = this.l / N;
    this.tau = T / K;
    this.sigma = (a * a * this.tau * this.tau) / (this.h * this.h);

    const gridImp = implicitScheme(N, K, a, this.tau, this.h);
    const gridExp = explicitScheme(N, K, a, this.tau, this.h);
    const gridAnal = analSolutionGrid(N, K, a, this.tau, this.h);

    const layoutExplicit = {
      title: 'Explicit',
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
    const dataExplicit = [{
      z: gridExp,
      type: 'surface'
    }];
    Plotly.newPlot('explicit', dataExplicit, layoutExplicit);

    const layoutImplicit = {
      title: 'Implicit',
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
    const dataImplicit = [{
      z: gridImp,
      type: 'surface'
    }];
    Plotly.newPlot('implicit', dataImplicit, layoutImplicit);

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

    const expTrace = {
      // x: Array.from(Array(gridExp.length).keys()),
      y: gridExp.map(s => this.sum(s) / s.length),
      type: 'scatter',
      name: 'Explicit'
    };

    const impTrace = {
      // x: Array.from(Array(gridExp.length).keys()),
      y: gridImp.map(s => this.sum(s) / s.length),
      type: 'scatter',
      name: 'Implicit'
    };

    const analTrace = {
      // x: Array.from(Array(gridExp.length).keys()),
      y: gridAnal.map(s => this.sum(s) / s.length),
      type: 'scatter',
      name: 'Analytic'
    };

    Plotly.newPlot('solution-comparison', [expTrace, impTrace, analTrace]);
  }

  sum = arr => arr.reduce((a, b) => a + b, 0);

}
