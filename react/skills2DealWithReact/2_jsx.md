# 2.4 JSX 문법

-   div 대신 fragment도 사용 가능

❓리액트 컴포넌트에서 왜 하나의 컴포넌트로 감싸야 함?

⇒ Virtual DOM에서 효율적으로 컴포넌트 변화를 감지해낼 수 있게 트리 구조로 이뤄져야 하기 때문.

## 삼항 연산자 대신 AND 연산자

```jsx
import "./App.css";

function App() {
    const name = "리액트";
    return <div>{name === "리액트" && <h1>아닌데</h1>}</div>;
}

export default App;
```

위 return문에 적힌 것처럼 name === 리액트가 true이면 옆의 h1 태그도 렌더가 됨.

반대로 name ≠ 리액트이면 옆의 h1 태그는 렌더링이 되지 않고 null이 렌더가 되는 듯
