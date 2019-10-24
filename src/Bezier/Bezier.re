type point = {
  x: float,
  y: float,
};

type bezierCurve = {
  p1: point,
  p2: point,
  p3: point,
  p4: point,
};

type action =
  | MoveP1(point)
  | MoveP2(point)
  | MoveP3(point)
  | MoveP4(point);

let bezierCurveReducer = (state, action) =>
  switch (action) {
  | MoveP1(p1) => {...state, p1}
  | MoveP2(p2) => {...state, p2}
  | MoveP3(p3) => {...state, p3}
  | MoveP4(p4) => {...state, p4}
  };
let twoPointArray = (p1, p2) => [|p1.x, p1.y, p2.x, p2.y|];

let bezierCurveArray = ({p1, p2, p3, p4}) =>
  [|twoPointArray(p1, p2), twoPointArray(p3, p4)|]->Relude.Array.flatten;

module Circle = {
  let getXY = shape => {x: Konva.Shape.x(shape), y: Konva.Shape.y(shape)};
  [@react.component]
  let make = (~update, ~point, ~dispatch: action => unit) =>
    <Konva.Circle
      x={point.x}
      y={point.y}
      radius=3.
      fill="red"
      draggable=true
      onDragMove={e => e->Konva.Event.targetGet->getXY->update->dispatch}
    />;
};

[@react.component]
let make = (~initialPoints) => {
  let (state, dispatch) =
    React.useReducer(bezierCurveReducer, initialPoints);
  <>
    <Konva.Line
      points=state->bezierCurveArray
      stroke="green"
      strokeWidth=0.3
      bezier=true
    />
    <Circle update={p => MoveP1(p)} point={state.p1} dispatch />
    <Circle update={p => MoveP2(p)} point={state.p2} dispatch />
    <Circle update={p => MoveP3(p)} point={state.p3} dispatch />
    <Circle update={p => MoveP4(p)} point={state.p4} dispatch />
    <Konva.Line
      points={twoPointArray(state.p1, state.p2)}
      stroke="red"
      strokeWidth=0.3
    />
    <Konva.Line
      points={twoPointArray(state.p3, state.p4)}
      stroke="red"
      strokeWidth=0.3
    />
  </>;
};
