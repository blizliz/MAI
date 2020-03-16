import { Component, OnInit } from '@angular/core';

declare var Plotly: any;
declare var tridiagonalMatrixAlgorithm: any;

function psi(x) {
  // return x + Math.sin(Math.PI  * x);
  return Math.cos(x);
}

function phi0(t, a) {
  return Math.exp(-a * t);
}

function phil(t, a) {
  return -Math.exp(-a * t);
}

function analSolutionFun(x, t, a) {
  return Math.exp( -a * t) * Math.cos(x);
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
  const sigma = koeff * koeff * tau / (h * h);
  const grid = [];
  grid[0] = [];
  grid[0].push(1);
  for (let j = 1; j < N - 1; j++) {
    const x = j * h;
    grid[0][j] = psi(x);
  }
  grid[0][N - 1] = -1;

  for (let k = 1; k < K; k++) {
    grid[k] = [];
    const t = k * tau;
    grid[k].push(Math.exp(-koeff * t));
    for (let j = 1; j < N - 1; j++) {
      grid[k][j] = sigma * grid[k - 1][j + 1]
                 + (1 - 2 * sigma) * grid[k - 1][j]
                 + sigma * grid[k - 1][j - 1];
    }
    grid[k][N - 1] = -Math.exp(-koeff * t);
  }
  return grid;
}

function implicitScheme(N, K, koeff, tau, h) {
  const sigma = koeff * koeff * tau / (h * h);
  const grid = [];
  grid[0] = [];
  grid[0].push(1);
  for (let j = 1; j < N - 1; j++) {
    const x = j * h;
    grid[0][j] = psi(x);
  }
  grid[0][N - 1] = -1;

  for (let k = 1; k < K; k++) {
    grid[k] = [];
    const a = [];
    const b = [];
    const c = [];
    const d = [];

    a.push(0);
    b.push(-(1 + 2 * sigma));
    c.push(sigma);
    d.push(-(grid[k - 1][0] + sigma * phi0(k * tau, koeff)));
    for (let j = 1; j < N - 1; j++) {
      a.push(sigma);
      b.push(-(1 + 2 * sigma));
      c.push(sigma);
      d.push(-grid[k - 1][j]);
    }
    a.push(sigma);
    b.push(-(1 + 2 * sigma));
    c.push(0);
    d.push(-(grid[k - 1][N - 1] + sigma * phil(k * tau, koeff)));

    grid[k] = tridiagonalMatrixAlgorithm(a, b, c, d);
  }
  return grid;
}

function CrankNicholsonSchemes(N, K, koeff, tau, h) {
  const theta = 0.5;
  const sigma = koeff * koeff * tau / (h * h);
  const grid = [];
  grid[0] = [];
  grid[0].push(1);
  for (let j = 1; j < N - 1; j++) {
    const x = j * h;
    grid[0][j] = psi(x);
  }
  grid[0][N - 1] = -1;

  for (let k = 1; k < K; k++) {
    // implicit
    let tmpImp = [];
    grid[k] = [];
    const a = [];
    const b = [];
    const c = [];
    const d = [];

    a.push(0);
    b.push(-(1 + 2 * sigma));
    c.push(sigma);
    d.push(-(grid[k - 1][0] + sigma * phi0(k * tau, koeff)));
    for (let j = 1; j < N - 1; j++) {
      a.push(sigma);
      b.push(-(1 + 2 * sigma));
      c.push(sigma);
      d.push(-grid[k - 1][j]);
    }
    a.push(sigma);
    b.push(-(1 + 2 * sigma));
    c.push(0);
    d.push(-(grid[k - 1][N - 1] + sigma * phil(k * tau, koeff)));

    tmpImp = tridiagonalMatrixAlgorithm(a, b, c, d);

    // explicit
    const tmpExp = [];
    const t = k * tau;
    tmpExp.push(Math.exp(-koeff * t));
    for (let j = 1; j < N - 1; j++) {
      tmpExp[j] = sigma * grid[k - 1][j + 1]
        + (1 - 2 * sigma) * grid[k - 1][j]
        + sigma * grid[k - 1][j - 1];
    }
    tmpExp[N - 1] = -Math.exp(-koeff * t);

    for (let j = 0; j < tmpExp.length; j++) {
      grid[k][j] = theta * tmpImp[j] + (1 - theta) * tmpExp[j];
    }
  }
  return grid;
}

@Component({
  selector: 'app-lab1',
  templateUrl: './lab1.component.html',
  styleUrls: ['./lab1.component.css']
})

export class Lab1Component implements OnInit {
  l = Math.PI;
  h;
  tau;
  sigma;

  constructor() { }

  solve(N, K, a, T) {
    a = +a;
    N = +N;
    K = +K;
    this.h = this.l / N;
    this.tau = T / K;
    this.sigma = a * a * this.tau / (this.h * this.h);

    const gridImp = implicitScheme(N, K, a, this.tau, this.h);
    const gridExp = explicitScheme(N, K, a, this.tau, this.h);
    const gridAnal = analSolutionGrid(N, K, a, this.tau, this.h);
    const gridCN = CrankNicholsonSchemes(N, K, a, this.tau, this.h);

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

    const errorExp = [];
    for (let i = 0; i < gridExp.length; i++) {
      errorExp[i] = [];
      for (let j = 0; j < gridExp[i].length; j++) {
        errorExp[i][j] = Math.abs(gridAnal[i][j] - gridExp[i][j]);
      }
    }
    const errorImp = [];
    for (let i = 0; i < gridImp.length; i++) {
      errorImp[i] = [];
      for (let j = 0; j < gridImp[i].length; j++) {
        errorImp[i][j] = Math.abs(gridAnal[i][j] - gridImp[i][j]);
      }
    }
    const errorCN= [];
    for (let i = 0; i < gridCN.length; i++) {
      errorCN[i] = [];
      for (let j = 0; j < gridCN[i].length; j++) {
        errorCN[i][j] = Math.abs(gridAnal[i][j] - gridCN[i][j]);
      }
    }

    const expTrace = {
      // x: Array.from(Array(gridExp.length).keys()),
      y: errorExp.map(s => this.sum(s) / s.length),
      type: 'scatter',
      name: 'Explicit'
    };

    const impTrace = {
      // x: Array.from(Array(gridExp.length).keys()),
      y: errorImp.map(s => this.sum(s) / s.length),
      type: 'scatter',
      name: 'Implicit'
    };

    const CNTrace = {
      // x: Array.from(Array(gridExp.length).keys()),
      y: errorCN.map(s => this.sum(s) / s.length),
      type: 'scatter',
      name: 'CrankNicholson'
    };

    Plotly.newPlot('solution-comparison', [expTrace, impTrace, CNTrace]);

    const layoutCN = {
      title: 'CN',
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
    const dataCN = [{
      z: gridCN,
      type: 'surface'
    }];
    Plotly.newPlot('cn', dataCN, layoutCN);
  }

  sum = arr => arr.reduce((a, b) => a + b, 0);

  ngOnInit() {
  }
}
